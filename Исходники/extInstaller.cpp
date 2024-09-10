bool CExtInstaller::GetChromeResPathByReg(std::string &chromeAppPath, std::string chromeVersion)
{
	if( false == GetInstallPath(CHROME_UNINSTALL_REG_PATH, chromeAppPath))
	{
		return false;
	}
	SHOW_LOG( "CExtInstaller::GetChromeResPathByReg GetInstallPath chromepath %s\n", chromeAppPath.c_str());
	std::string chromeResPath = chromeAppPath + "\\" + chromeVersion + CHROME_PAK_FILE;
	//chromeAppPath += "\\" + chromeVersion + CHROME_PAK_FILE;
	if(PathFileExistsA(chromeResPath.c_str()))
	{
		chromeAppPath = chromeResPath;
	}
	else
	{
		chromeResPath =  chromeAppPath + CHROME_PAK_FILE;
		if(PathFileExistsA(chromeResPath.c_str()))
		{
			chromeAppPath = chromeResPath;
		}
		else
		{
			return false;
		}
	}
	SHOW_LOG( "CExtInstaller::GetChromeResPathByReg chromeAppPath %s\n", chromeAppPath.c_str());
	return true;