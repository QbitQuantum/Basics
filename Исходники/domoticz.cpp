int main(int argc, char**argv)
#endif
{
#if defined WIN32
	CreateMutexA(0, FALSE, "Local\\Domoticz"); 
    if(GetLastError() == ERROR_ALREADY_EXISTS) { 
		MessageBox(HWND_DESKTOP,"Another instance of Domoticz is already running!","Domoticz",MB_OK);
        return -1; 
	}
	bool bStartWebBrowser=true;
	RedirectIOToConsole();
#endif

	szStartupFolder="";
	szWWWFolder="";
#if !defined WIN32
	char szStartupPath[255];
	getExecutablePathName((char*)&szStartupPath,255);
	szStartupFolder=szStartupPath;
	if (szStartupFolder.find_last_of('/')!=std::string::npos)
		szStartupFolder=szStartupFolder.substr(0,szStartupFolder.find_last_of('/')+1);
#else
	#ifndef _DEBUG
		char szStartupPath[255];
		char * p;
		GetModuleFileName(NULL, szStartupPath, sizeof(szStartupPath));
		p = szStartupPath + strlen(szStartupPath);

		while(p >= szStartupPath && *p != '\\')
			p--;

		if(++p >= szStartupPath)
			*p = 0;
		szStartupFolder=szStartupPath;
		size_t start_pos = szStartupFolder.find("\\Release\\");
		if(start_pos != std::string::npos) {
			szStartupFolder.replace(start_pos, 9, "\\domoticz\\");
			_log.Log(LOG_NORM,"%s",szStartupFolder.c_str());
		}
	#endif
#endif
	GetAppVersion();
	_log.Log(LOG_NORM,"Domoticz V%s (c)2012-2014 GizMoCuz",szAppVersion.c_str());

#if !defined WIN32
	//Check if we are running on a RaspberryPi
	std::string sLine = "";
	std::ifstream infile;

	infile.open("/proc/cpuinfo");
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			getline(infile, sLine);
			if (sLine.find("BCM2708")!=std::string::npos)
			{
				_log.Log(LOG_NORM,"System: Raspberry Pi");
				bIsRaspberryPi=true;
				break;
			}
		}
		infile.close();
	}
	_log.Log(LOG_NORM,"Startup Path: %s", szStartupFolder.c_str());
#endif

	szWWWFolder=szStartupFolder+"www";

	CCmdLine cmdLine;

	// parse argc,argv 
#if defined WIN32
	cmdLine.SplitLine(__argc, __argv);
#else
	cmdLine.SplitLine(argc, argv);
#endif

	if ((cmdLine.HasSwitch("-h"))||(cmdLine.HasSwitch("--help"))||(cmdLine.HasSwitch("/?")))
	{
		_log.Log(LOG_NORM,szHelp);
		return 0;
	}

	if (cmdLine.HasSwitch("-startupdelay"))
	{
		if (cmdLine.GetArgumentCount("-startupdelay")!=1)
		{
			_log.Log(LOG_ERROR,"Please specify a startupdelay");
			return 0;
		}
		int DelaySeconds=atoi(cmdLine.GetSafeArgument("-startupdelay",0,"").c_str());
		_log.Log(LOG_NORM,"Startup delay... waiting %d seconds...",DelaySeconds);
		sleep_seconds(DelaySeconds);
	}

	if (cmdLine.HasSwitch("-www"))
	{
		if (cmdLine.GetArgumentCount("-www")!=1)
		{
			_log.Log(LOG_ERROR,"Please specify a port");
			return 0;
		}
		std::string wwwport=cmdLine.GetSafeArgument("-www",0,"8080");
		_mainworker.SetWebserverPort(wwwport);
	}
	if (cmdLine.HasSwitch("-nowwwpwd"))
	{
		_mainworker.m_bIgnoreUsernamePassword=true;
	}

	std::string dbasefile=szStartupFolder + "domoticz.db";
#ifdef WIN32
	if (!IsUserAnAdmin())
	{
		char szPath[MAX_PATH];
		HRESULT hr = SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath);
		if (SUCCEEDED(hr))
		{
			std::string sPath=szPath;
			sPath+="\\Domoticz";

			DWORD dwAttr = GetFileAttributes(sPath.c_str());
			BOOL bDirExists=(dwAttr != 0xffffffff && (dwAttr & FILE_ATTRIBUTE_DIRECTORY));
			if (!bDirExists)
			{
				BOOL bRet=CreateDirectory(sPath.c_str(),NULL);
				if (bRet==FALSE) {
					MessageBox(0,"Error creating Domoticz directory in program data folder (%ProgramData%)!!","Error:",MB_OK);
				}
			}
			sPath+="\\domoticz.db";
			dbasefile=sPath;
		}
	}
#endif

	if (cmdLine.HasSwitch("-dbase"))
	{
		if (cmdLine.GetArgumentCount("-dbase")!=1)
		{
			_log.Log(LOG_ERROR,"Please specify a Database Name");
			return 0;
		}
		dbasefile=cmdLine.GetSafeArgument("-dbase",0,"domoticz.db");
	}
	_mainworker.m_sql.SetDatabaseName(dbasefile);

	if (cmdLine.HasSwitch("-wwwroot"))
	{
		if (cmdLine.GetArgumentCount("-wwwroot")!=1)
		{
			_log.Log(LOG_ERROR,"Please specify a WWW root path");
			return 0;
		}
		std::string szroot=cmdLine.GetSafeArgument("-wwwroot",0,"");
		if (szroot.size()!=0)
			szWWWFolder=szroot;
	}

	if (cmdLine.HasSwitch("-verbose"))
	{
		if (cmdLine.GetArgumentCount("-verbose")!=1)
		{
			_log.Log(LOG_ERROR,"Please specify a verbose level");
			return 0;
		}
		int Level=atoi(cmdLine.GetSafeArgument("-verbose",0,"").c_str());
		_mainworker.SetVerboseLevel((eVerboseLevel)Level);
	}
#if defined WIN32
	if (cmdLine.HasSwitch("-nobrowser"))
	{
		bStartWebBrowser=false;
	}
#endif
	if (cmdLine.HasSwitch("-log"))
	{
		if (cmdLine.GetArgumentCount("-log")!=1)
		{
			_log.Log(LOG_ERROR,"Please specify an output log file");
			return 0;
		}
		std::string logfile=cmdLine.GetSafeArgument("-log",0,"domoticz.log");
		_log.SetOutputFile(logfile.c_str());
	}

	if (!_mainworker.Start())
	{
		return 0;
	}

	signal(SIGINT, catch_intterm); 
	signal(SIGTERM,catch_intterm);
	
	/* now, lets get into an infinite loop of doing nothing. */

#if defined WIN32
#ifndef _DEBUG
	RedirectIOToConsole();	//hide console
#endif
	InitWindowsHelper(hInstance,hPrevInstance,nShowCmd,DQuitFunction,atoi(_mainworker.GetWebserverPort().c_str()),bStartWebBrowser);
	MSG Msg;
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
#else
	for ( ;; )
		sleep_seconds(1);
#endif
	return 0;
}