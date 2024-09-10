/*----------------------------------------------------------------------------*/
int SigAliveWrite(char* sProcessId)
/*----------------------------------------------------------------------------*/
{
	BOOL flag = TRUE;
	
	LOG(_FL_, 0, 0, "Process_Alive..[%s]", sProcessId);
	
	int iProcess = 1;
	
	if (flag)
	{
		/*
		 * DAT 파일에 메시지를 쓴다.
		 */

		FILE* fp;
		FILE* fp2;
		FILE* fp3;
		char sFileName[128];
		char strLine[MAX_LINE_SIZE];

        char* p = CfgGetMst("ib.path.file.ps_alive");
        
		if (p == NULL)
		{
			LOG(_FL_, 9, 0, "ERROR : PS_ALIVE 파일 미정의");
			return -1;
		}

		strcpy(sFileName, p);
		UtilSetYYYYMMDD(sFileName);

		if (flag)
		{
			if (flag)
			{
				/* 폴더를 확인한다. 없으면 만든다. */
				char sPath[128];
				strcpy(sPath, sFileName);

				char* p = rindex(sPath, '/');
				*p = 0x00;
				if (!flag) LOG(_FL_, 0, 0, "[sPath:%s]", sPath);

				if (access(sPath, R_OK) < 0)
				{
					/* 폴더가 없으면 생성한다. */
					mkdir(sPath, 0750);
					
					LOG(_FL_, 9, 0, "폴더 생성=[%s]", sPath);
				}
			}

			if (flag)
			{
				/* PS_ALIVE 파일을 확인하여 없으면 생성한다. */
				if (access(sFileName, W_OK) < 0)
				{
					/* 파일이 없으면 생성한다. */
					fp = fopen(sFileName, "w");
					
					fclose(fp);
					
					LOG(_FL_, 9, 0, "파일 생성=[%s]", sFileName);
				}
			}

			if (flag)  /* 변경 */
			{
			    /* DAT 파일을 오픈한다. */
				fp2 = fopen(sFileName, "r+");
				if (fp2 == NULL)
				{
					LOG(_FL_, 9, 0, "ERROR : FILE 정보 open error...[%s]", sFileName);
					
					return -1;
				}
				
				while ( 1 )
				{
					strLine[0] = 0x00;
		
					long pos = ftell(fp2);
					char* p = fgets(strLine, MAX_LINE_SIZE, fp2);
					if (p == NULL)
						break;
		
					LOAD_ALIVE* pDat = (LOAD_ALIVE*) &strLine;
					
					if (strncmp(pDat->sFepId, sProcessId, 10) == 0)
					{
						
						memcpy(pDat->sAlive, "_ALIVE_", 7);
						memcpy(pDat->sTime, TimeGetTime(), 6);
						sprintf(pDat->sSec, "%10.10d", time(NULL) );
		                pDat->sLF[0] = 0x00;
		
						fseek(fp2, pos, SEEK_SET);
						fputs(strLine, fp2);
		
		                iProcess = 0;
					}
				}
		
				/* 처리된 파일을 닫는다. */
				fclose(fp2);
			}
			
			
			if (flag)  /* 시간체크 */
			{
			    /* DAT 파일을 오픈한다. */
				fp3 = fopen(sFileName, "r+");
				if (fp3 == NULL)
				{
					LOG(_FL_, 9, 0, "ERROR : FILE 정보 open error...[%s]", sFileName);
					
					return -1;
				}
		
				while ( 1 )
				{
					strLine[0] = 0x00;
		
					long pos = ftell(fp3);
					char* p = fgets(strLine, MAX_LINE_SIZE, fp3);
					if (p == NULL)
						break;
		
					LOAD_ALIVE* pDat = (LOAD_ALIVE*) &strLine;
					
					int iDiff = time(NULL) - atoi(pDat->sSec);
					
					if (iDiff >  20 && strncmp(pDat->sAlive, "_ALIVE_", 7) == 0 && strncmp(pDat->sFepId, "MAACOM0000", 10) == 0)
					{
						LOG(_FL_, 9, 0, "[%s]프로세스 30초 경과 -> CHECK 변경", pDat->sFepId);
						memcpy(pDat->sAlive, "_CHECK_", 7);
						memcpy(pDat->sTime, TimeGetTime(), 6);
		                pDat->sLF[0] = 0x00;
		
						fseek(fp2, pos, SEEK_SET);
						fputs(strLine, fp2);
		
		                iProcess = 0;
					}
					
					if (iDiff > 120 && strncmp(pDat->sAlive, "_ALIVE_", 7) == 0)
					{
						LOG(_FL_, 9, 0, "120초 경과 -> CHECK 변경");
						memcpy(pDat->sAlive, "_CHECK_", 7);
						memcpy(pDat->sTime, TimeGetTime(), 6);
		                pDat->sLF[0] = 0x00;
		
						fseek(fp2, pos, SEEK_SET);
						fputs(strLine, fp2);
		
		                iProcess = 0;
					}
				}
		
				/* 처리된 파일을 닫는다. */
				fclose(fp3);
			}
	
			
		}
		

		if (flag)  /* 신규 등록 */
		{
	        if ( iProcess == 1 ) {
	        	
				/* DAT 파일을 오픈한다. */
				fp = fopen(sFileName, "a");
				if (fp == NULL)
				{
					LOG(_FL_, 9, 0, "ERROR : FILE 정보 open error...[%s]", sFileName);
					if (flag) exit(-1);
					return -1;            /* TODO DATE.2013.11.07 */
				}
    
				fprintf(fp, "%10.10s%8.8s%6.6s%7.7s%10.10d\n"
					, sProcessId
					, TimeGetDate()
		            , TimeGetTime()
		            , "_ALIVE_"
		            , time(NULL) );
		
				fflush(fp);
	
				/* 처리된 파일을 닫는다. */
				fclose(fp);
				}
		}
	}

	return;
}