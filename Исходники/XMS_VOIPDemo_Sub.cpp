// -----------------------------------------------------------------------
void   WriteMsgLog(char *pMsg)
{
	FILE   *fp;
	char   tmpTime[128], tmpDate[128];

	char   LogFileName[256] = {0}; 
	char   LogFileShortName[] = "\\VOIPSysMsgLogDemo.txt";
	char   MsgStr[512] = {0};
		
	if (pMsg == NULL)
		return;

	GetCurrentDirectory(MAX_FILE_NAME_LEN-32, LogFileName);
	strcat(LogFileName, LogFileShortName);

	if ((fp = fopen(LogFileName, "a+t")) == NULL)
	{
		sprintf(MsgStr, "fopen(%s) error.", LogFileName);
		AddMsg(MsgStr);		
	}
	else
	{		
		_strtime(tmpTime);
		_strdate(tmpDate);
		
		sprintf(MsgStr, "%s %s  %s\n",tmpDate ,tmpTime, pMsg);
		fwrite(MsgStr, strlen(MsgStr), 1, fp);
	}

	if (fp != NULL)
		fclose(fp);	
	
}