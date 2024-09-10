// this is the static initialize phase is called via constructor
// Has to occur BEFORE init()
// manages to detect Multimonitorsystems, and ScreensaverMode..
void ScreensaverApp::initialize()
{
	iScreensaverMode=InterpreteCommandLine();

	BOOL	blnCloneMode=CRegistry::MatrixShow[REGISTRY_CLONE];

	EnumDisplayMonitors(GetDC(NULL),NULL,(MONITORENUMPROC) MonitorEnum, (long)&blnCloneMode);

	SetCursor(NULL);

}