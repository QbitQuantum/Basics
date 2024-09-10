void dbugfile_init()
{
	// Clear the counters
	memset(dbugfile_counters, 0, sizeof(int) * MAX_COUNTERS);

	char big_buffer[1000];
	char temp_buff[512];

	dbugfile_filename[0] = '\0';

#ifdef _WIN32

	char path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);

	int path_len = strlen(path);
	if(path[path_len - 1] != '\\')
	{
	 	path[path_len] = '\\';
		path[path_len + 1] = '\0';
	}

 	strcpy(dbugfile_filename, path);

#endif

	strcat(dbugfile_filename, "DBUG-");
	strcpy(big_buffer, "DBUGFILE Active: ");

#ifdef _WIN32
	{
		unsigned long len = 512;
		GetUserName(temp_buff, &len);
		
		strcat(dbugfile_filename, temp_buff);
		strcat(big_buffer, temp_buff);
		
		strcat(dbugfile_filename, "-");
		strcat(big_buffer, " ");
	}
#endif

    _tzset();

    // Display operating system-style date and time.
	_strdate( temp_buff);
	strcat(dbugfile_filename, "D(");
	strcat(dbugfile_filename,temp_buff);
	strcat(big_buffer,temp_buff);

	strcat(dbugfile_filename, ") T(");
	strcat(big_buffer, " ");

    _strtime( temp_buff);
	strcat(dbugfile_filename,temp_buff);
	strcat(big_buffer,temp_buff);

	strcat(dbugfile_filename, ").txt");
	strcat(big_buffer, "\n");

	// Remove invalid slash chars
	int len = strlen(dbugfile_filename);
	while(len >= 2)
	{
		if(dbugfile_filename[len] == '/' || dbugfile_filename[len] == ':')
		{
			dbugfile_filename[len] = '-';
		}
		len--;
	}

	// open file
	// Uncomment this to see where the file is going
  	//MessageBox(NULL, dbugfile_filename, "das", MB_OK); 
	FILE *fp = fopen(dbugfile_filename, "w");

	if(fp == NULL)
	{
		return;
	}

	fwrite(big_buffer, sizeof(char) * strlen(big_buffer), 1, fp);

#ifdef _WIN32

	// detect OS type

	OSVERSIONINFO version_info;
	version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if(GetVersionEx(&version_info) != false)
	{
		char *error = "Error in detecting OS version";
		char *version = error;

		switch(version_info.dwMajorVersion)
		{
			case 4:
			{
				if(version_info.dwMinorVersion == 0)
				{
					version = "Windows 95"; 
				}
				else if(version_info.dwMinorVersion == 10)
				{
					version = "Windows 98";  
				}
				else if(version_info.dwMinorVersion == 90)
				{
					version = "Windows Me";
				}
				break;
			}
			case 5:
			{
				if(version_info.dwMinorVersion == 0)
				{
					version = "Windows 2000"; 
				}
				else if(version_info.dwMinorVersion == 1)
				{
					version = "Windows XP";
				}
				break;
			}
		}

		char *release_type = NULL;
#ifdef _DEBUG 
		release_type = "Debug";
#else
		release_type = "Release";
#endif
		sprintf(big_buffer, "OS: %s %s, ", version, release_type);
	}				  

	fwrite(big_buffer, sizeof(char) * strlen(big_buffer), 1, fp);

	char exe_name[MAX_PATH];

	GetModuleFileName(NULL, exe_name, MAX_PATH);
	strcat(exe_name, "\n");
	fwrite(exe_name, sizeof(char) * strlen(exe_name), 1, fp);


#endif

	fclose(fp);

	dbugfile_init_var = true;
}