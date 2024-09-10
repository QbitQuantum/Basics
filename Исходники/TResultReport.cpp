int CTResultReport::LogDataCAL(char* sn,char *datetime,char* filename,char* pData)
{
	FILE *fLog;	
	
	char PathBuf[256]="";
	char FileName[512]="";
	char cal_log_folder[512]="";
	int iFileOpenErr = 0;
	
	if(!GetCurrentDirectory(sizeof(PathBuf), PathBuf))
	{
        return FALSE;
	}
	else
	{
		sprintf_s(FileName, sizeof(FileName), "%s\\NF_Data\\", PathBuf,sn,datetime);

		sprintf_s(cal_log_folder, sizeof(cal_log_folder), "%s\\NF_Data\\NF_%s_%s\\", PathBuf,sn,datetime);
		if(!PathFileExists(FileName))
		{	
			if(!CreateDirectory(FileName,NULL))
			{
				amprintf("Create Folder Fail!\n");
				return 0;
			}
		}
		if(!PathFileExists(cal_log_folder))
		{	
			if(!CreateDirectory(cal_log_folder,NULL))
			{
				amprintf("Create Folder Fail!\n");
				return 0;
			}
		}
        strcat_s(cal_log_folder, sizeof(cal_log_folder), filename);

		iFileOpenErr = fopen_s(&fLog, cal_log_folder, "a+");
		if(NULL == fLog)
		{
			return FALSE;
		}
		fprintf_s(fLog,"%s\n",pData);
		fclose(fLog);

	}

	return TRUE;
}