void
LogStats(int code,long recv,long send)
{
char szFileName[MAX_PATH];
char tempchar[128];
HANDLE hFile=NULL;
FILE *f;
	if (GetModuleFileName(NULL, szFileName, MAX_PATH))
					{
						char* p = strrchr(szFileName, '\\');
						*p = '\0';
						strcat_s (szFileName,MAX_PATH,"\\");
						strcat_s (szFileName,MAX_PATH,_itoa(code,tempchar,10));
						strcat_s (szFileName,MAX_PATH,".txt");
					}

	if ((f = fopen((LPCSTR)szFileName, "a")) != NULL)
		{
			char	msg[100];
			char	buf[5];
			SYSTEMTIME	st; 
			GetLocalTime(&st);
			_itoa(st.wYear,buf,10);
			strcpy(msg,buf);
			strcat(msg,"/");
			_itoa(st.wMonth,buf,10);
			strcat(msg,buf);
			strcat(msg,"/");
			_itoa(st.wDay,buf,10);
			strcat(msg,buf);
			strcat(msg," ");
			_itoa(st.wHour,buf,10);
			strcat(msg,buf);
			strcat(msg,":");
			_itoa(st.wMinute,buf,10);
			strcat(msg,buf);
			strcat(msg,":");
			_itoa(st.wSecond,buf,10);
			strcat(msg,buf);
			strcat(msg," ");
			strcat(msg,"Transmitted: ");
			strcat(msg,_ltoa((send+recv)/512,tempchar,10));
			strcat(msg,"k \n");
	
			fprintf(f,msg);
			fclose(f);
	}
}