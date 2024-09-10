//! constructor
CIrrDeviceConsole::CIrrDeviceConsole(const SIrrlichtCreationParameters& params, const char* dataPak)
  : CIrrDeviceStub(params, dataPak), IsWindowFocused(true), ConsoleFont(0), OutFile(stdout)
{
	DeviceToClose = this;

#ifdef _IRR_WINDOWS_NT_CONSOLE_
	MouseButtonStates = 0;

	WindowsSTDIn  = GetStdHandle(STD_INPUT_HANDLE);
	WindowsSTDOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PCOORD Dimensions = 0;

	if (CreationParams.Fullscreen)
	{
// Some mingw versions lack this define, so avoid it in case it does not exist
#if (_WIN32_WINNT >= 0x0501) && defined(CONSOLE_FULLSCREEN_MODE)
		if (SetConsoleDisplayMode(WindowsSTDOut, CONSOLE_FULLSCREEN_MODE, Dimensions))
		{
			CreationParams.WindowSize.Width = Dimensions->X;
			CreationParams.WindowSize.Width = Dimensions->Y;
		}
#endif
	}
	else
	{
		COORD ConsoleSize;
		ConsoleSize.X = CreationParams.WindowSize.Width;
		ConsoleSize.X = CreationParams.WindowSize.Height;
		SetConsoleScreenBufferSize(WindowsSTDOut, ConsoleSize);
	}

	// catch windows close/break signals
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE);

#elif defined(_IRR_POSIX_API_)
	// catch other signals
	signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT,  &sighandler);

	// set output stream
	if (params.WindowId)
		OutFile = (FILE*)(params.WindowId);
#endif

#ifdef _IRR_VT100_CONSOLE_
	// reset terminal
	fprintf(OutFile, "%cc", 27);
	// disable line wrapping
	fprintf(OutFile, "%c[7l", 27);
#endif

	switch (params.DriverType)
	{
	case video::EDT_SOFTWARE:
		#ifdef _IRR_COMPILE_WITH_SOFTWARE_
		VideoDriver = video::createSoftwareDriver(CreationParams.WindowSize, CreationParams.Fullscreen, FileSystem, this);
		#else
		os::Printer::log("Software driver was not compiled in.", ELL_ERROR);
		#endif
		break;

	case video::EDT_BURNINGSVIDEO:
		#ifdef _IRR_COMPILE_WITH_BURNINGSVIDEO_
		VideoDriver = video::createBurningVideoDriver(CreationParams, FileSystem, this);
		#else
		os::Printer::log("Burning's Video driver was not compiled in.", ELL_ERROR);
		#endif
		break;

	case video::EDT_DIRECT3D8:
	case video::EDT_DIRECT3D9:
	case video::EDT_OPENGL:
		os::Printer::log("The console device cannot use hardware drivers yet.", ELL_ERROR);
		break;
	case video::EDT_NULL:
		VideoDriver = video::createNullDriver(FileSystem, CreationParams.WindowSize);
		break;
	default:
		break;
	}

	// set up output buffer
	for (u32 y=0; y<CreationParams.WindowSize.Height; ++y)
	{
		core::stringc str;
		str.reserve(CreationParams.WindowSize.Width);
		for (u32 x=0; x<CreationParams.WindowSize.Width; ++x)
			str += " ";
		OutputBuffer.push_back(str);
	}


#ifdef _IRR_WINDOWS_NT_CONSOLE_
	CursorControl = new CCursorControl(CreationParams.WindowSize);
#endif

	if (VideoDriver)
	{
		createGUIAndScene();
#ifdef _IRR_USE_CONSOLE_FONT_
		if (GUIEnvironment)
		{
			ConsoleFont = new gui::CGUIConsoleFont(this);
			gui::IGUISkin *skin = GUIEnvironment->getSkin();
			if (skin)
			{
				for (u32 i=0; i < gui::EGDF_COUNT; ++i)
					skin->setFont(ConsoleFont, gui::EGUI_DEFAULT_FONT(i));
			}
		}
#endif
	}
}