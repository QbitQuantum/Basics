int _tmain(int argc, _TCHAR* argv[])
{
	GLogger.Timestamping()=true;
	GLogger.DebugString()="AgfmAgent";
	GLogger.OutputConsole()=true;
	GLogger.Open(::ExeDirectory()+"Debug.txt");
	GLogger.DebugLevel()=5;
	GLogger.Fatal("Start AGFM Agent\n");
//	EventLogger.Register();
#ifdef _WINDOWS
	_set_se_translator( trans_func );   //Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions
	// MICHALOSKI ADDED
	TCHAR buf[1000];
	GetModuleFileName(NULL, buf, 1000);
	std::string path(buf);
	path=path.substr( 0, path.find_last_of( '\\' ) +1 );
	SetCurrentDirectory(path.c_str());
#endif
	// check for 		inifile=::ExeDirectory() + "Config.ini";	

	AgentConfigurationEx config;
	config.setAgent(new Agent());
	Globals.Debug = 5;
	GLogger.Fatal("Call main\n");
	return config.main(argc, (const char **) argv);

	return 0;
}