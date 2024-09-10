void WriteApplicationFile(char *mappname,char* MessageString)
{
	try
	{
		char mmCurentDir[512];
		SYSTEMTIME systime;

		
		char mdate[255]={0};
		char mmdate[255]={0};
		char mtime[255]={0};
		char mmFileName[512]={0};
		bool isFileExist;
		char mlogtype[1024]={0};
		bool isPerDeleted=false;
		
		//lstrcpy(mmCurentDir , mAPPLOG);
		//strcpy(mmCurentDir,SAAZODSetUpPath);
		lstrcat(mmCurentDir ,"ApplicationLog\\");
		//strcat(mmCurentDir , "\\Log");

		GetLocalTime(&systime);

		sprintf(mdate  , "%04d-%02d-%02d" ,systime.wYear, systime.wDay , systime.wMonth );
		sprintf(mmdate , "%04d%02d%02d" ,systime.wYear, systime.wDay , systime.wMonth);
		//GetTimeFormat(LOCALE_SYSTEM_DEFAULT , NULL , &systime , "hh':'mm':'ss" , mtime , 255);
		sprintf(mtime , "%02d:%02d:%02d" , systime.wHour, systime.wMinute , systime.wSecond);
		sprintf(mmFileName , "%s\\%s.Log" , mmCurentDir , mappname);
		FILE *fp=NULL;

		if(IsDirExist(mmFileName) == false)
		{
			isFileExist = false;
			fp=fopen( mmFileName ,"w+"); //for wiping out the contents
			_fcloseall( );
		}
		else
		{
			isFileExist = true;
		}

		DWORD dwFileSize = IsFile2MB(mmFileName);// Check for 2 MB (2097152 Bytes)

		if(dwFileSize >= 2097152)
		{
			isPerDeleted = true;
			isFileExist = false;
			fp=fopen( mmFileName ,"w+"); //For wiping out the contents
			_fcloseall( );
		}
		
		fp = fopen( mmFileName , "a");
		if(!(fp == NULL))
		{
			if (isFileExist == false)
			{
				fprintf(fp , "#Software: %s\n#Version: 1.0 \n#Date: %s %s\n# \n" , "zSmart.exe", mdate , mtime);
				fprintf(fp , "----------------------------------------------------------------------\n" );
				//fprintf(fp , "#Fields:\tdtime\tSession Id\tSession User Name\tmodule\n");
				if(isPerDeleted == true)
				{
					fprintf(fp , "Previous content is deleted. Due to the size limit of 2 MB\n" );
					fprintf(fp , "----------------------------------------------------------------------\n" );
				}
			}

				
			fprintf(fp , "%s %s\t%s \n" , mdate , mtime , MessageString);
		
		}
		else
		{ 

		}
		_fcloseall( );
	}
	catch(...)
	{
	}
}