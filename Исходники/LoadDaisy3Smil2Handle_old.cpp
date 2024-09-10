void LoadDaisy3Smil2Handle::endElement  (const XMLCh *const uri, 
										 const XMLCh *const localname, 
										 const XMLCh *const qName)
{
	char* message4 = XMLString::transcode(localname);
	
	//Check the variable which its value are true;
	//		TRUE  means don't pass its function for store data from file to our variable.
	//		FALSE means complete, don't do anything more!

	  //////////////////
	 // Checking par //
	//////////////////
	if  (!strcmp(message4,"par") || !strcmp(message4,"Par") || !strcmp(message4,"PAR")) 
	{		
		if ( ((intCountAudio == 1) && (boolNewAudio = true))
		   ||((intCountText  == 1) && (boolNewText  = true))	 
		   ||((intCountImg   == 1) && (boolNewImg   = true)))
		{
			//push back seq information
			vecDaisy3Smil2BodySeqId.push_back			(strDaisy3Smil2BodySeqTempId);
			vecDaisy3Smil2BodySeqClass.push_back		(strDaisy3Smil2BodySeqTempClass);	
			vecDaisy3Smil2BodySeqCustomTest.push_back	(strDaisy3Smil2BodySeqTempCustomTest);
			vecDaisy3Smil2BodySeqDur.push_back			(strDaisy3Smil2BodySeqTempDur);
			vecDaisy3Smil2BodySeqXmlLang.push_back		(strDaisy3Smil2BodySeqTempXmlLang);
			vecDaisy3Smil2BodySeqEnd.push_back			(strDaisy3Smil2BodySeqTempEnd);
			vecDaisy3Smil2BodySeqFill.push_back			(strDaisy3Smil2BodySeqTempFill);
			_itoa_s(intDaisy3Smil2BodySeqTempLevel, a, 10);		//convert int to string
			vecDaisy3Smil2BodySeqLevel.push_back		(a);	//store that string to vector
			//push back par information
			vecDaisy3Smil2BodyParId.push_back			(strDaisy3Smil2BodyParTempId);
			vecDaisy3Smil2BodyParClass.push_back		(strDaisy3Smil2BodyParTempClass);
			vecDaisy3Smil2BodyParCustomTest.push_back	(strDaisy3Smil2BodyParTempCustomTest);
			vecDaisy3Smil2BodyParXmlLang.push_back		(strDaisy3Smil2BodyParTempXmlLang);
			_itoa_s(intDaisy3Smil2BodyParTempLevel, a, 10);		//convert int to string
			vecDaisy3Smil2BodyParLevel.push_back		(a);	//store that string to vector

			//push back Anchor <a> information
			vecDaisy3Smil2BodyAnchorId.push_back		(strDaisy3Smil2BodyAnchorTempId);
			vecDaisy3Smil2BodyAnchorClass.push_back		(strDaisy3Smil2BodyAnchorTempClass);
			vecDaisy3Smil2BodyAnchorTitle.push_back		(strDaisy3Smil2BodyAnchorTempTitle);
			vecDaisy3Smil2BodyAnchorXmlLang.push_back	(strDaisy3Smil2BodyAnchorTempXmlLang);
			vecDaisy3Smil2BodyAnchorHref.push_back		(strDaisy3Smil2BodyAnchorTempHref);
			vecDaisy3Smil2BodyAnchorExternal.push_back	(strDaisy3Smil2BodyAnchorTempExternal);
			//push back image information
			vecDaisy3Smil2BodyImgId.push_back			(strDaisy3Smil2BodyImgTempId);
			vecDaisy3Smil2BodyImgRegion.push_back		(strDaisy3Smil2BodyImgTempRegion);
			vecDaisy3Smil2BodyImgSrc.push_back			(strDaisy3Smil2BodyImgTempSrc);
			vecDaisy3Smil2BodyImgType.push_back			(strDaisy3Smil2BodyImgTempType);
			vecDaisy3Smil2BodyImgXmlLang.push_back		(strDaisy3Smil2BodyImgTempXmlLang);
			//push back text infomation
			vecDaisy3Smil2BodyTextId.push_back			(strDaisy3Smil2BodyTextTempId);
			vecDaisy3Smil2BodyTextSrcFile.push_back		(strDaisy3Smil2BodyTextTempSrc.substr(0,strDaisy3Smil2BodyTextTempSrc.find("#")));		//Seperte File and ID
			vecDaisy3Smil2BodyTextSrcId.push_back		(strDaisy3Smil2BodyTextTempSrc.substr(strDaisy3Smil2BodyTextTempSrc.find("#")+1));		//Seperte File and ID	
			vecDaisy3Smil2BodyTextType.push_back		(strDaisy3Smil2BodyTextTempType);
			vecDaisy3Smil2BodyTextRegion.push_back		(strDaisy3Smil2BodyTextTempRegion);
			vecDaisy3Smil2BodyTextXmlLang.push_back		(strDaisy3Smil2BodyTextTempXmlLang);
			vecDaisy3Smil2BodyTextContent.push_back		("WaItInG");
			//push back audio infomation
			vecDaisy3Smil2BodyAudioId.push_back			(strDaisy3Smil2BodyAudioTempId);
			vecDaisy3Smil2BodyAudioSrc.push_back		(strDaisy3Smil2BodyAudioTempSrc);
			vecDaisy3Smil2BodyAudioType.push_back		(strDaisy3Smil2BodyAudioTempType);
			vecDaisy3Smil2BodyAudioClipBegin.push_back	(strDaisy3Smil2BodyAudioTempClipBegin);
			vecDaisy3Smil2BodyAudioClipEnd.push_back	(strDaisy3Smil2BodyAudioTempClipEnd);
			vecDaisy3Smil2BodyAudioRegion.push_back		(strDaisy3Smil2BodyAudioTempRegion);
			vecDaisy3Smil2BodyAudioXmlLang.push_back	(strDaisy3Smil2BodyAudioTempXmlLang);

			//setup variable
			if (intCountImg   == 1)
				intCountImg   =  0;
			if (intCountText  == 1)
				intCountText  =  0;
			if (intCountAudio == 1)
				intCountAudio =  0;
		}

		//setup variable for find level of par in this SMIL.
		intDaisy3Smil2BodyParTempLevel--;
		return;
	}

	  ////////////////////////
	 // Checking seq and a //
	////////////////////////
	if  ( !strcmp(message4,"seq") 
		||!strcmp(message4,"Seq") 
		||!strcmp(message4,"SEQ")
		||!strcmp(message4,"a")
		||!strcmp(message4,"A"))
	{
		//setup variable
		if (intCountImg   > 0)
			intCountImg--;
		if (intCountText  > 0)
			intCountText--;
		if (intCountAudio > 0)
			intCountAudio--;

		//only seq
		if  (!strcmp(message4,"seq") || !strcmp(message4,"Seq") || !strcmp(message4,"SEQ")) 
		{
			//setup variable for find level od seq in this SMIL.
			intDaisy3Smil2BodySeqTempLevel--;
		}
		return;
	}
}