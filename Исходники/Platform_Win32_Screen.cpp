Platform_Win32_Screen::Platform_Win32_Screen(Platform_Win32_OS* os):
	windowHandle_(os->GetWindowHandle()),
	technology_(Technology_Undefined),
	technologyInstance_(0),
	fullscreen_(true),
	fullscreenWidth_(0),
	fullscreenHeight_(0),
	showfps_(false),
	interpolationMode_(true),
	disableOnWmSize_(0),
	ignoreNextOnWmSize_(false),
	firstTimeInitializeCalled_(false),
	forceddraw_(false),
	forcegdi_(false)
	{
	Platform::RegisterEventListener(this);

	// Check commandline flags
	if (os->GetCommandLineString())
		{
		char* cmdline=strdup(os->GetCommandLineString());
		char* token=strtok(cmdline," ");
		while (token)
			{
			if (stricmp(token,"-window")==0)
				{
				fullscreen_=false;
				}
			if (stricmp(token,"-showfps")==0)
				{
				showfps_=true;
				}
			if (stricmp(token,"-forceddraw")==0)
				{
				forceddraw_=true;
				}
			if (stricmp(token,"-forcegdi")==0)
				{
				forcegdi_=true;
				}

			token=strtok(0," ");
			}
		free(cmdline);
		}

	// Determine default screen size
	HWND desktopWindow=GetDesktopWindow();
	RECT desktopRect;
	BOOL result=GetWindowRect(desktopWindow,&desktopRect);
	if (result)
		{
		fullscreenWidth_=desktopRect.right-desktopRect.left;
		fullscreenHeight_=desktopRect.bottom-desktopRect.top;

		windowedWidth_=fullscreenWidth_-fullscreenWidth_/6;
		windowedHeight_=fullscreenHeight_-fullscreenHeight_/6;
		windowedX_=fullscreenWidth_-windowedWidth_;
		windowedY_=fullscreenHeight_-windowedHeight_;
		windowedX_/=2;
		windowedY_/=2;
		}



	}