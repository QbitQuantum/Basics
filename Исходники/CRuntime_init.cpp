// Initialise runtime
bool CRuntime::Initialise(CRuntimeSetup* crSetup)
{
	// Start by getting and saving the CPU capabilities.
	DWORD cpuFeatures = GetCPUCaps();
	supportMMX = cpuFeatures & CPU_FEATURE_MMX;
	supportSSE = cpuFeatures & CPU_FEATURE_SSE;
	supportSSE2 = cpuFeatures & CPU_FEATURE_SSE2;

	// Construct requires MMX for collisions
#ifndef APPRUNTIME
	if (!supportMMX)
		throw runtime_error("Your CPU does not support MMX technology (it must be pretty old!).  Please buy a newer PC then try again!");

#endif

	// Save hInstance
	hInstance = crSetup->hInstance;

	CapReader.pRuntime = this;

	CreateTempDirectory();

	// Get app properties
	BYTE* pData;
	int dataSize;
	HGLOBAL hData = OpenResourceBinary(997, "APPBLOCK", pData, dataSize);
	CapReader.ReadAppProperties(pData, dataSize, props);
	FreeResource(hData);

	// Cannot use both multisampling and motion blur
#ifndef APPRUNTIME
	if (multisamples > 0 && motionBlur)
		throw runtime_error("Cannot enable both multisamples and motion blur.  Please change one of these settings.");
#endif

#ifdef PYTHON
	// Get python
	hData = OpenResourceBinary(992, "PYTHONLIBS", pData, dataSize);
	CapReader.ReadPythonResources(pData, dataSize);
	FreeResource(hData);
	if(!SearchPath(NULL, "python26.dll", NULL, 0, NULL, NULL))
		throw runtime_error("Python26.dll was not found and is required to run this application or feature.  Reinstalling the application "
								"may fix this problem.");
	Py_Initialize();
#endif

	// Get menu resources
	hData = OpenResourceBinary(993, "MENUBLOCK", pData, dataSize);
	CapReader.ReadMenuResources(pData, dataSize, menus);
	FreeResource(hData);

	crSetup->winWidth = props.winWidth;
	crSetup->winHeight = props.winHeight;
	crSetup->eyeDistance = props.eyeDistance;
	crSetup->screensaver = props.screensaver;
	fpsMode = props.fpsMode;
	userFps = props.fps;

	//if (disableWindowsKey)
	//	g_hKeyboardHook = SetWindowsHookEx( WH_KEYBOARD_LL,  DisableWinKeyKeyboardProc, hInstance, 0);

#ifdef CONSTRUCT_DIRECTX9
	crSetup->display_params.fps_mode = props.fpsMode;
	crSetup->display_params.fullscreen = fullscreen = props.fullscreen;
	crSetup->display_params.backbuffer_width = props.winWidth;
	crSetup->display_params.backbuffer_height = props.winHeight;

	switch (multisamples) {
	case 0:	// Off
		crSetup->display_params.multisamples = 0;
		break;
	case 1: // 2x
		crSetup->display_params.multisamples = 2;
		break;
	case 2:	// 4x
		crSetup->display_params.multisamples = 4;
		break;
	case 3: // 8x
		crSetup->display_params.multisamples = 8;
		break;
	default:
		crSetup->display_params.multisamples = 0;
		break;
	}

	// PreInit gets the D3D caps and allows MakeWindows to create the correct number of windows to pass to Init()
	//Display.SetMultiMonitorMode(MMM_CLONE);
	//Display.PreInit();
	renderer.LoadD3D();
#endif

#ifndef CONSTRUCT_SDL
	// Create a window for the runtime
	if (!MakeWindows(crSetup))
		throw runtime_error("Cannot create window");
#else
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		exit(1);

	// Register SDL_Quit to be called at exit; makes sure things are cleaned up when we quit.
	atexit(SDL_Quit);
    
	// Attempt to create window with 32bit pixels in hardware
	Display.screen = SDL_SetVideoMode(props.winWidth, props.winHeight, 32, SDL_HWSURFACE);
	SDL_SetAlpha(Display.screen, SDL_SRCALPHA, 255); // Set alpha to normal
#endif

	InitCommonControls();

	// The preview runtimes show the runtime in the title bar.
#ifdef CONSTRUCT_PREVIEW
	#ifdef CONSTRUCT_DIRECTX9
	props.appTitle += " (DX9 runtime)";
	#endif
	#ifdef APPRUNTIME
	props.appTitle += " (App runtime)";
	#endif
	#ifdef CONSTRUCT_SDL
	props.appTitle += " (SDL runtime)";
	#endif
#endif

#ifndef CONSTRUCT_SDL
	SetWindowText(hWnds.front(), props.appTitle);
#else
	SDL_WM_SetCaption(props.appTitle, NULL);
#endif

	// Restore mouse cursor from hourglass
	if (!props.screensaver)
		SetCursor(LoadCursor(NULL, IDC_ARROW));

	// Load a menu
	if (props.UseMenu)
		if (menus.size() != 0)
			SetMenu(hWnds.front(), menus[0]);

#ifndef APPRUNTIME
#ifndef CONSTRUCT_SDL
	// Direct-X setup
	crSetup->display_params.hWnds = hWnds;
	crSetup->display_params.hFocusWnd = hWnds.front();

	winWidthOffset = 0;
	winHeightOffset = 0;

	// Retrieve all display modes: can't set an invalid display mode size
	if (crSetup->display_params.fullscreen) {
		BOOL bRetVal;
		DEVMODE devMode;
		int iMode = 0;

		int wantedWidth = crSetup->display_params.backbuffer_width;
		int wantedHeight = crSetup->display_params.backbuffer_height;
		int bestWidth = 100000;
		int bestHeight = 100000;

		bool found = false;

		do
		{
			bRetVal = ::EnumDisplaySettings(NULL, iMode, &devMode);
			iMode++;

			if (bRetVal)
			{
				int curWidth = devMode.dmPelsWidth;
				int curHeight = devMode.dmPelsHeight;

				// Display mode found!
				if (curWidth == wantedWidth && curHeight == wantedHeight)
					found = true;

				// This display mode is big enough to fit the display in, but is smaller than the last best size
				if ((curWidth >= wantedWidth && curHeight >= wantedHeight)
					&& (curWidth < bestWidth && curHeight < bestHeight)) {
					bestWidth = curWidth;
					bestHeight = curHeight;
				}
			}
		}
		while (bRetVal);

		// Identical display mode not found: use next best that can fit it all on
		if (!found) {

			// Still 100000x100000: no resolution found that supports this
			if (bestWidth == 100000 || bestHeight == 100000)
				throw runtime_error("The display resolution required by this application is not supported.");

	#ifdef CONSTRUCT_PREVIEW
			CString msg;
			msg.Format("Switching to Fullscreen mode: Display mode %d x %d not supported, switching to next best %d x %d.\n\n"
				"The 'Window Width' and 'Window Height' values in Application Properties define the fullscreen resolution.",
				crSetup->display_params.backbuffer_width, crSetup->display_params.backbuffer_height, bestWidth, bestHeight);
			MessageBox(NULL, msg, "Fullscreen preview", MB_OK | MB_ICONEXCLAMATION);
	#endif

			crSetup->display_params.backbuffer_width = wantedWidth = bestWidth;
			crSetup->display_params.backbuffer_height = wantedHeight = bestHeight;
		}
	}

	// Set the eye distance before we initialize
	eyeDistance = crSetup->eyeDistance;
	renderer.SetEyeDistance(eyeDistance);

	// Start up the display engine
	//Display.Init(&(crSetup->d3dDisplaySetup));
	renderer.CreateDevice(crSetup->display_params);

	/*
	// No identical match for display mode
	if (crSetup->d3dDisplaySetup.resWidth != actualDisplayWidth || crSetup->d3dDisplaySetup.resHeight != actualDisplayHeight)
		if (tempDisplayTarget == unallocated_texture)
			tempDisplayTarget = CreateDisplayTargetTexture();

		winWidthOffset = (actualDisplayWidth - crSetup->d3dDisplaySetup.resWidth) / 2;
		winHeightOffset = (actualDisplayHeight - crSetup->d3dDisplaySetup.resHeight) / 2;
	}
	*/

	GetSwapChains();

	// Multi-monitor settings require the temp display target

	if (renderer.GetMultiMonitorMode() != cr::multimonitor_singlescreen) {
		if (tempDisplayTarget == unallocated_texture)
				tempDisplayTarget = CreateDisplayTargetTexture();
	}

	// Linear resizers
	if (props.sampler == 0) {
		renderer.SetSamplerState(cr::ss_magfilter, cr::ssv_point);
		renderer.SetSamplerState(cr::ss_minfilter, cr::ssv_point);
	}
	if (props.sampler == 1) {
		renderer.SetSamplerState(cr::ss_magfilter, cr::ssv_linear);
		renderer.SetSamplerState(cr::ss_minfilter, cr::ssv_linear);
	}

	// Premultiplied alpha mode
	renderer.SetAlphaBlending();

	// Runtime uses clamp-sampling
	renderer.SetSamplerState(cr::ss_addressu, cr::ssv_clamp);
	renderer.SetSamplerState(cr::ss_addressv, cr::ssv_clamp);

	// Create the multisampling target if one required
	//if (multisamples > 0)		// 0 is off
	//	multisampleTargets[0] = renderer.CreateRenderTargetTexture(crSetup->winWidth, crSetup->winHeight, cr::texture_format_a8r8g8b8, true);

#if defined(CONSTRUCT_DIRECTX9) && defined(CONSTRUCT_PREVIEW)
	// Handle shader simulation
	if (simShader != SS_NOSIM) {

		UINT ps_major = D3DSHADER_VERSION_MAJOR(renderer.GetCaps().PixelShaderVersion);
		UINT ps_minor = D3DSHADER_VERSION_MINOR(renderer.GetCaps().PixelShaderVersion);

		CString hardwarePS;
		hardwarePS.Format("%d.%d", ps_major, ps_minor);

		CString simulatedPS;

		switch (simShader) {
		case SS_PS14:
			simulatedPS = "1.4";
			break;
		case SS_PS11:
			simulatedPS = "1.1";
			break;
		case SS_PS00:
			simulatedPS = "0.0";
			break;
		}

		float ps_version = atof(hardwarePS);
		float sim_version = atof(simulatedPS);

		// If fullscreen MessageBox()'s won't work
		if (!fullscreen) {
		
			if (sim_version > ps_version) {
				CString msg;
				msg.Format("You have chosen to simulate a pixel shader version (PS %s) higher than your hardware supports (PS %s).  "
					"You can only simulate lower hardware capabilities.  The application will continue to use PS %s.",
					simulatedPS, hardwarePS, simulatedPS);
				MessageBox(NULL, msg, "Simulate shader", MB_OK | MB_ICONEXCLAMATION);
			}
			else if (sim_version == ps_version) {
				CString msg;
				msg.Format("You have chosen to simulate the same pixel shader version as your hardware supports (PS %s).  "
					"The application will continue normally.", hardwarePS);
				MessageBox(NULL, msg, "Simulate shader", MB_OK | MB_ICONINFORMATION);
			}
			else {
				CString msg;
				msg.Format("You are simulating pixel shader %s capabilites.  Your hardware supports pixel shader %s.",
					simulatedPS, hardwarePS);
				MessageBox(NULL, msg, "Simulate shader", MB_OK | MB_ICONEXCLAMATION);
			}

		}
	}
#endif // shader sims
#endif

	// Load the PNG image list
	hData = OpenResourceBinary(995, "IMAGEBLOCK", pData, dataSize);
	CapReader.ReadImageData(pData, dataSize, imagehandle_to_address);
	FreeResource(hData);

#ifdef CONSTRUCT_DIRECTX9
	// Initialise DirectInput
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
								IID_IDirectInput8, (void**)&dinput, NULL)))
		throw runtime_error("Failed to initialise DirectInput.  Please ensure you have DirectX 8 or above installed!");

	// Initialize the keyboard
	if (FAILED(dinput->CreateDevice(GUID_SysKeyboard, &d_keyboard, NULL)))
		throw runtime_error("Failed to initialise DirectInput.");
	if (FAILED(d_keyboard->SetDataFormat(&c_dfDIKeyboard)))
		throw runtime_error("Failed to initialise DirectInput.");

	if (FAILED(d_keyboard->SetCooperativeLevel(hWnds.front(), DISCL_BACKGROUND |
											 DISCL_NONEXCLUSIVE)))
		throw runtime_error("Failed to initialise DirectInput.");

	if (FAILED(d_keyboard->Acquire()))
		throw runtime_error("Failed to initialise DirectInput.");

	// initialize the mouse
	if (FAILED(dinput->CreateDevice(GUID_SysMouse, &d_mouse, NULL)))
		throw runtime_error("Failed to initialise DirectInput.");
	if (FAILED(d_mouse->SetCooperativeLevel(hWnds.front(), DISCL_BACKGROUND |
										  DISCL_NONEXCLUSIVE)))
		throw runtime_error("Failed to initialise DirectInput.");

	if (FAILED(d_mouse->SetDataFormat(&c_dfDIMouse)))
		throw runtime_error("Failed to initialise DirectInput.");

	if (FAILED(d_mouse->Acquire()))
		throw runtime_error("Failed to initialise DirectInput.");

	inputState.isDirectInput = true;

#endif
#endif //#ifndef APPRUNTIME

	// Save window dimensions
	winWidth = crSetup->winWidth;
	winHeight = crSetup->winHeight;
	RECT clientSize;
	GetClientRect(hWnds.front(), &clientSize);
	realWinWidth = clientSize.right - clientSize.left;
	realWinHeight = clientSize.bottom - clientSize.top;

	// Unpack dependencies before loading plugins
	UnpackDependencies();

	// Unpack the resource plugins to the temp dir and load them
	UnpackPlugins(1000);

	// Read the frame data
	hData = OpenResourceBinary(998, "LEVELBLOCK", pData, dataSize);
	CapReader.ReadFrameData(pData, dataSize);
	FreeResource(hData);

	// Map object type names to their pointers
	for (vector<CRunObjType*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		CString lowername = (*i)->Name;
		lowername.MakeLower();
		name_to_object[lowername] = *i;
	}

#ifdef CONSTRUCT_DEBUGGER
	// Create debugger once object types are known but before parsing event block (which may send logs)
	// Create invisible initially
	pDebug->Create();
	pDebug->ShowWindow(SW_HIDE);
#endif

	// Read the CAP event tree
	hData = OpenResourceBinary(999, "EVENTBLOCK", pData, dataSize);
	CapReader.ReadEventList(pData, dataSize);
	FreeResource(hData);

	// Iterate all events determining their modifiers
	vector<CRunLayout*>::iterator f = Frames.begin();
	const vector<CRunLayout*>::const_iterator Frames_end = Frames.end();

	for ( ; f != Frames_end; f++) {
		EventIterator e = (*f)->Events.begin();
		EventConstIterator Events_end = (*f)->Events.end();

		for ( ; e != Events_end; ++e) {

			// Recurse down tree finding SOL modifiers
			(*e)->GetSolModifiers(*f);

			// If this event line is a group, it can be marked as top level for optimisation
			if ((*e)->GetType() == EVENT_GROUP)
				((CEventGroup*)*e)->isTopLevel = true;
		}
	}

	// Initialise effects
#ifdef CONSTRUCT_DIRECTX9
	hData = OpenResourceBinary(994, "HLSL", pData, dataSize);
	CapReader.ReadHLSLData(pData, dataSize);
	FreeResource(hData);

	// If motionblur is required, set up the textures
	if (motionBlur) {

		InitMotionBlur();

	}

#endif //APPRUNTIME

	// Clock offset (timers relative to Run())
	clockOffset = clock();
	curFrame = 0;

	// Mark objects which are not to serialize
	CRunObjType* pNoSerialize = GetTypeFromName("No serialize");

	if (pNoSerialize) {
		if (!pNoSerialize->teams.empty()) {
			ObjTypeIterator t = pNoSerialize->teams.begin();
			ObjTypeIterator end = pNoSerialize->teams.end();

			for ( ; t != end; t++)
				(*t)->noSerialize = true;
		}		
	}

	// Set current frame
	CRunLayout* pFirstFrame = Frames.front();
	runningFrames.push_back(pFirstFrame);
	system.pLayout = pFirstFrame;
	pFirstFrame->systemDrawn = true;
	pFirstFrame->Load();

	// Load any other layouts which want their textures loaded on startup
	vector<CRunLayout*>::iterator ly = Frames.begin();
	ly++;	// already loaded 1st layout

	for ( ; ly != Frames.end(); ++ly) {
		if ((*ly)->texture_loading == CRunLayout::tl_load_on_app_start)
			(*ly)->LoadLayoutTextures();
		else if ((*ly)->texture_loading == CRunLayout::tl_use_app_setting && texture_loading == tl_load_on_app_start)
			(*ly)->LoadLayoutTextures();
	}

	// Directories exist etc. by now.
	completedInitialisation = true;

	// Initial frame mouse coord
	POINT mouse;
	GetCursorPos(&mouse);

	if (!fullscreen)
		ScreenToClient(hWnds.front(), &mouse);

	pFirstFrame->mouseX = mouse.x;
	pFirstFrame->mouseY = mouse.y;

	// Create initial frame objects (generatevent works)
	pFirstFrame->CreateInitialObjects();

	FlushDelayedObjects();

	system.changeResWidth = winWidth;
	system.changeResHeight = winHeight;

	// Start of Layout triggered only if not previewing another layout
	if (previewLayout <= 0)
		GenerateEvent(-1, SYSTEM_STARTOFFRAME, NULL);

#ifdef CONSTRUCT_DEBUGGER
	pDebug->ShowWindow(SW_SHOW);
	pDebug->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	pDebug->ModifyStyleEx(0, WS_EX_TOPMOST);
#endif

	// Previewing single layout?
	if (previewLayout > 0)		// if == 0, no need to jump anywhere, already on layout 1
		system.DoFrameChange(previewLayout, "none", 0);

	return true;
}