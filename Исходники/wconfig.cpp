static bool S9xSaveConfigFile(ConfigFile &conf){

	configMutex = CreateMutex(NULL, FALSE, TEXT("Snes9xConfigMutex"));
	int times = 0;
	DWORD waitVal = WAIT_TIMEOUT;
	while(waitVal == WAIT_TIMEOUT && ++times <= 150) // wait at most 15 seconds
		waitVal = WaitForSingleObject(configMutex, 100);

	// save over the .conf file if it already exists, otherwise save over the .cfg file
	std::string	fname;
	fname=S9xGetDirectory(DEFAULT_DIR);
	fname+=SLASH_STR S9X_CONF_FILE_NAME;

	// ensure previous config file is not lost if we crash while writing the new one
	std::string	ftemp;
	{
		CopyFileA(fname.c_str(), (fname + ".autobak").c_str(), FALSE);

		ftemp=S9xGetDirectory(DEFAULT_DIR);
		ftemp+=SLASH_STR "config_error";
		FILE* tempfile = fopen(ftemp.c_str(), "wb");
		if(tempfile) fclose(tempfile);
	}

	bool ret = try_save(fname.c_str(), conf);

	remove(ftemp.c_str());
	remove((fname + ".autobak").c_str());

	ReleaseMutex(configMutex);
	CloseHandle(configMutex);

	return ret;
}