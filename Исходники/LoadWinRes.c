INT ParseResToWin(CHAR* pResFile)
{
	FILE* pFile;
	INT  iCurState;
	INT  iCurStrLen;
	CHAR czCurStr[256];

	CList list;
	PList pList;
	PWindow pWin;
	
	
	pFile = fopen(pResFile, "w+");
	if(pFile == NULL)
	{
		return -1;
	}

	iCurState = PARSE_STATE_START;
	iCurStrLen = 0;
	MemSet(czCurStr, 0, sizeof(czCurStr));

	InitList(&list);
	pList = &list;
	
	while(TRUE)
	{
		switch(iCurState)
		{
			case PARSE_STATE_START:
				czCurStr[iCurStrLen] = GetNextAvaliChar(pFile, "\n	 ", 3);
				iCurStrLen++;
				iCurStrLen += GetStringUntil(pFile, czCurStr+1, "\n	 ", 3);

				if(MemCmp(czCurStr, WIN_RES_FLAG_WINDOW_START, iCurStrLen) == 0)
				{
					iCurState = PARSE_STATE_WINSTART;
				}

				if(MemCmp(czCurStr, WIN_RES_FLAG_WINDOW_END, iCurStrLen) == 0)
				{
					iCurState = PARSE_STATE_WINEND;
				}

				iCurStrLen = 0;
			break;

			case PARSE_STATE_WINSTART:
				pWin = (PWindow)Malloc(sizeof(CWindow));
				PushList(pList, pWin);				
				iCurState = PARSE_STATE_START;
			break;

			case PARSE_STATE_WINEND:
				
				iCurState = PARSE_STATE_START;
			break;

			case 

			case PARSE_STATE_ATTR_ID:

			break;

			case PARSE_STATE_STRING:

			break;

			case PARSE_STATE_LABEL:

			break;

			case PARSE_STARE_END:

			break;

			default:

			break;
		}
	}

	fclose(pFile);
	return 0;
}