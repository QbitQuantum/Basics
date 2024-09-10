static void initialize_path()
{
	char mclmcrrt_name[_MAX_PATH];
	char* pSysPath=NULL;
	char matlabroot[_MAX_PATH];
	memset(matlabroot,_MAX_PATH,0);
    build_mclmcrrt_name("9","0","0",mclmcrrt_name);
	if (pSysPath = getenv("PATH"))
	{
		char* newPath = (char *) malloc((strlen(pSysPath)+_MAX_PATH+1)*sizeof(char));
		char* pch =NULL;
		newPath[0]='\0';
		strcat(newPath,"PATH=");
		strcat(newPath,pSysPath);
		pch = strtok(pSysPath,";");
		while (pch != NULL) {
			char filepath[_MAX_PATH];
			strcpy(filepath,pch);
			strcat(filepath,"\\");
			strcat(filepath,mclmcrrt_name);
			if (file_exist(filepath)) {
				strcpy(matlabroot,pch);
				strcat(matlabroot,"\\..\\..");
				break;
			}
			pch = strtok(NULL,";");
		}
		if (strlen(matlabroot)!=0)
		{
			strcat(matlabroot,"\\bin\\");
			strcat(matlabroot,"win64");
			strcat(newPath,";");
			strcat(newPath,matlabroot);
			_putenv(newPath);
		}
        free(newPath);
	}
}