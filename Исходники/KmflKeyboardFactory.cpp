std::vector<EkayaKeyboard*>
KmflKeyboardFactory::loadKeyboards(const char * installPath)
{
	std::vector<EkayaKeyboard*> keyboards;
    MessageLogger::logMessage("Loading keyboards\n");
	char* appDir = NULL;
    size_t requiredSize;
	
    getenv_s( &requiredSize, NULL, 0, "APPDATA");
	appDir = new char[requiredSize];
	if (!appDir)
		return keyboards;
	std::string basePath;
	std::string pattern;
	if (appDir)
	{
		getenv_s( &requiredSize, appDir, requiredSize, "APPDATA" );
		basePath = std::string(appDir) + THANLWINSOFT_KMFL_DIR;
		pattern = basePath + KMFL_PATTERN;
	}
	else
	{
		return keyboards;
	}
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA ffd;

	// read files in user's APPDATA dir
	hFind = FindFirstFileA(pattern.c_str(), &ffd);
	while (INVALID_HANDLE_VALUE != hFind)
	{
        std::string kmflFileName = basePath + ffd.cFileName;
        MessageLogger::logMessage("Loading %s\n", kmflFileName.c_str());
		int kmflId = kmfl_load_keyboard((kmflFileName).c_str());
		if (kmflId > -1)
		{
			keyboards.push_back(new KmflKeyboard(kmflId, basePath, ffd.cFileName));
		}
        else
        {
            MessageLogger::logMessage("Failed to load %s\n", kmflFileName.c_str());
        }
		if (FindNextFileA(hFind, &ffd) == 0) break;
	}
	delete [] appDir;
    appDir = NULL;
	// read files under Program Files
    if (installPath == NULL)
    {
	    getenv_s( &requiredSize, NULL, 0, "ProgramFiles");
	    appDir = new char[requiredSize];
	    if (!appDir)
		    return keyboards;
    	getenv_s( &requiredSize, appDir, requiredSize, "ProgramFiles" );
        basePath = std::string(appDir) + THANLWINSOFT_KMFL_DIR;
    }
    else
    {
        basePath = std::string(installPath) + KMFL_DIR;
    }
	pattern = basePath + KMFL_PATTERN;
	hFind = FindFirstFileA(pattern.c_str(), &ffd);
	while (INVALID_HANDLE_VALUE != hFind)
	{
        std::string kmflFileName = basePath + ffd.cFileName;
        MessageLogger::logMessage("Loading %s\n", kmflFileName.c_str());
		int kmflId = kmfl_load_keyboard(kmflFileName.c_str());
		if (kmflId > -1)
		{
			keyboards.push_back(new KmflKeyboard(kmflId, basePath, ffd.cFileName));
		}
        else
        {
            MessageLogger::logMessage("Failed to load %s\n", kmflFileName.c_str());
        }
		if (FindNextFileA(hFind, &ffd) == 0) break;
	}
    if (installPath == NULL)
    {
	    delete [] appDir;
    }
    MessageLogger::logMessage("Loaded %d keyboards\n", keyboards.size());
	return keyboards;
}