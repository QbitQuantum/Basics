//
// this actually reads XSI or GLA headers...  historical mutation strikes again...
//
static void ReadASEHeader_Actual(LPCSTR psFilename, int &iStartFrame, int &iFrameCount, int &iFrameSpeed, bool bReadingGLA, bool bCanSkipXSIRead /* = false */)
{
	// since the XSI loader is so damn slow and flakey I'm going to have to cache the info to avoid re-reading...
	//

	// do we have it in the cache?...
	//
	if (strstr(psFilename,".xsi") || strstr(psFilename,".XSI"))
	{
		ASECachedInfo_t::iterator iter = ASECachedInfo.find(psFilename);
		if (iter != ASECachedInfo.end())
		{
			iStartFrame = 0;
			iFrameCount = (*iter).second.first;
			iFrameSpeed = (*iter).second.second;
			return;
		}
	}

	// is it a GLA file?...
	//
	if (bReadingGLA)
	{
		char sTemp[1024];
		strcpy(sTemp,psFilename);
		if (!(strstr(psFilename,".gla") || strstr(psFilename,".GLA")))
		{
			strcat(sTemp,".gla");
		}

		iStartFrame = 0;
		iFrameCount = GLA_ReadHeader(sTemp);
		iFrameSpeed = 20;	// any old value for GLA file
		return;
	}


	// it's not in the cache, but we may be able to avoid having to read it under some circumstances...
	//
	bool bXSIShouldBeRead = true;

	if (gbCarWash_DoingScan)
	{
		bCanSkipXSIRead = false;	// stop it asking the question
		bXSIShouldBeRead= gbCarWash_YesToXSIScan;
	}

	if ( (strstr(psFilename,".xsi") || strstr(psFilename,".XSI"))
		&& bCanSkipXSIRead
		)
	{
		if (!gbSkipXSIRead && !gbSkipXSIRead_QuestionAsked)
		{
			gbSkipXSIRead_QuestionAsked = true;
			gbSkipXSIRead = !GetYesNo(va("Model file: \"%s\"\n\n... is an XSI, and they can be damn slow to read in\n\nDo you want to scan all the XSIs?",psFilename));
		}
					
		bXSIShouldBeRead = !gbSkipXSIRead;
	}

	if (strstr(psFilename,".xsi") || strstr(psFilename,".XSI"))
	{
		if (bXSIShouldBeRead)
		{
			ReadXSIHeader(psFilename, iStartFrame, iFrameCount, iFrameSpeed);
	
			if (iFrameCount!=0)
			{
				// cache it for future...
				//
				ASECachedInfo[psFilename] = FrameCountAndSpeed_t(iFrameCount,iFrameSpeed);
			}
		}
		return;
	}

	// it must be an ASE file then instead....
	//
	CTokenizer* tokenizer = CTokenizer::Create();
	tokenizer->AddParseFile(psFilename, ((CAssimilateApp*)AfxGetApp())->GetBufferSize());
	tokenizer->SetSymbols(CSequence_s_Symbols);
	tokenizer->SetKeywords(CSequence_s_Keywords);

	CToken* curToken = tokenizer->GetToken();
	while(curToken != NULL)
	{
		switch (curToken->GetType())
		{
		case TK_EOF:
			curToken->Delete();
			curToken = NULL;
			break;
		case TK_ASTERISK:
			curToken->Delete();
			curToken = tokenizer->GetToken();
			switch(curToken->GetType())
			{
			case TK_ASE_FIRSTFRAME:
				curToken->Delete();
				curToken = tokenizer->GetToken();
				if (curToken->GetType() == TK_INTEGER)
				{
					iStartFrame = curToken->GetIntValue();
					curToken->Delete();
					curToken = tokenizer->GetToken();
				}
				break;
			case TK_ASE_LASTFRAME:
				curToken->Delete();
				curToken = tokenizer->GetToken();
				if (curToken->GetType() == TK_INTEGER)
				{
					iFrameCount = curToken->GetIntValue() + 1;
					curToken->Delete();
					curToken = NULL;	// tells outer loop to finish
				}
				break;
			case TK_ASE_FRAMESPEED:
				curToken->Delete();
				curToken = tokenizer->GetToken();
				if (curToken->GetType() == TK_INTEGER)
				{
					iFrameSpeed = curToken->GetIntValue();
					curToken->Delete();
					curToken = tokenizer->GetToken();
				}
				break;
			case TK_EOF:
				curToken->Delete();
				curToken = NULL;
				break;
			default:
				curToken->Delete();
				curToken = tokenizer->GetToken();
				break;
			}
			break;
		default:
			curToken->Delete();
			curToken = tokenizer->GetToken();
			break;
		}
	}
	tokenizer->Delete();

	iFrameCount -= iStartFrame;	
	iStartFrame  = 0;
}