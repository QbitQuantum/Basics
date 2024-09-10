int CfgFile::Open(char *filename)
{
	CFGTOKEN	token;
	PCFGSECTION	pCurrentSection	= NULL;	
	PCFGVALUE	pValue = NULL;
	int			ret				= CFG_NOERROR;

	m_nErrorLine = -1; m_nLineNum = 0;

	m_FilePointer = fopen(filename, "r");
	if(m_FilePointer == NULL) {
		ret = CFG_OPENFAIL;	
		goto return_label;
	}
	m_iptr = -1; m_pbptr = -1;
	ReadLine();

	while(1){		
		token = Scan();

		if( token.id == TEOF ){
			goto return_label;
		}
		if( token.id == TINVALID ){
			ret = CFG_INVALID;
			goto return_label;
		}

		switch(token.id){
		case TINTEGER :
		case TREAL :
		case TSTRING :
			if( pCurrentSection == NULL ){	// 만일 NULL이라면...
				pCurrentSection = new CFGSECTION("@GLOBAL");
				aSectionList.Add( pCurrentSection );
			}
			pValue = new CFGVALUE("<unnamed>");

			switch( token.id )
			{
			case TINTEGER:	pValue->SetInteger(token.v.nval); break;
			case TREAL:		pValue->SetReal(token.v.fval); break;
			case TSTRING:	pValue->SetString(token.v.szval); break;
			}

			pCurrentSection->aValList.Add(pValue);
			FreeToken(&token);
			break;
		case TSYMBOL :
			{
				pValue = new CFGVALUE(token.v.szval);
				FreeToken(&token);

				token = Scan();
				if(token.id != TEQUAL){
					ret = CFG_UNEXPECTED;
					delete pValue;
					goto return_label;
				}

				//INSTALL NEW VALUE
				token = Scan();
				if(token.id != TINTEGER && token.id != TREAL && token.id != TSTRING){
					ret = CFG_UNEXPECTED;
					delete pValue;
					goto return_label;
				}

				if( pCurrentSection == NULL ){	// 만일 NULL이라면...
					pCurrentSection = new CFGSECTION("@GLOBAL");
					aSectionList.Add( pCurrentSection );
				}
				
				//새로운 값을 추가해넣는다. 
				pCurrentSection->aValList.Add(pValue);
				switch( token.id )
				{
				case TINTEGER:	pValue->SetInteger(token.v.nval); break;
				case TREAL:		pValue->SetReal(token.v.fval); break;
				case TSTRING:	pValue->SetString(token.v.szval); break;
				}

				FreeToken(&token);
			}
			break;
		case TSECTION :
			{
				token = Scan();
				if( token.id != TSYMBOL ){
					ret = CFG_UNEXPECTED;
					goto return_label;
				}

				// MAKE NEW SECTION & ADD NEW SECTION TO SECTION LIST
				pCurrentSection = new CFGSECTION(token.v.szval);
				aSectionList.Add(pCurrentSection);
				FreeToken(&token);
			}
			break;
		default :
			ret = CFG_UNEXPECTED;
			goto return_label;
		}
		
		FreeToken(&token);
	}

return_label:
	if( ret != CFG_NOERROR ) m_nErrorLine = m_nLineNum;

	FreeToken(&token);

	if(m_FilePointer){
		fclose(m_FilePointer);
		m_FilePointer = NULL;
	}

	return ret;
}