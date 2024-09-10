BOOL CIMDisplayApp::InitInstance()
{
	if (!AfxOleInit())
		return FALSE;

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("ImageMagick"));

	LoadStdProfileSettings(5);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;

        //TH all image types, default
        pDocTemplate = new CMultiDocTemplate(
	        IDR_IMIMAGETYPE,
	        RUNTIME_CLASS(CIMDisplayDoc),
	        RUNTIME_CLASS(CChildFrame), // custom MDI child frame
	        RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // BMP
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMBMPTYPE,
		RUNTIME_CLASS(CIMDisplayDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // EPS
        pDocTemplate = new CMultiDocTemplate(
	        IDR_IMEPSTYPE,
	        RUNTIME_CLASS(CIMDisplayDoc),
	        RUNTIME_CLASS(CChildFrame), // custom MDI child frame
	        RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // GIF
        pDocTemplate = new CMultiDocTemplate(
	        IDR_IMGIFTYPE,
	        RUNTIME_CLASS(CIMDisplayDoc),
	        RUNTIME_CLASS(CChildFrame), // custom MDI child frame
	        RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // JPEG
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMJPEGTYPE,
		RUNTIME_CLASS(CIMDisplayDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // MIFF
        pDocTemplate = new CMultiDocTemplate(
	        IDR_IMMIFFTYPE,
	        RUNTIME_CLASS(CIMDisplayDoc),
	        RUNTIME_CLASS(CChildFrame), // custom MDI child frame
	        RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // PNG
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMPNGTYPE,
		RUNTIME_CLASS(CIMDisplayDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // TIFF
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMTIFFTYPE,
		RUNTIME_CLASS(CIMDisplayDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // SVG
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMSVGTYPE,
		RUNTIME_CLASS(CIMDisplayDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

        // WMF
        pDocTemplate = new CMultiDocTemplate(
	        IDR_IMWMFTYPE,
	        RUNTIME_CLASS(CIMDisplayDoc),
	        RUNTIME_CLASS(CChildFrame), // custom MDI child frame
	        RUNTIME_CLASS(CIMDisplayView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// BOGUS: find a way to generalize this!
	//char	exePath[2048];
	//DWORD	pathSize = GetModuleFileName( NULL, exePath, 2048 );
	//exePath[ pathSize ] = 0;
	//char*	ps = (char*)(exePath + pathSize - 1);
	//while ( *ps != '\\' )	{ *ps = 0; ps--; }	// shrink it!
        //MagickCore::InitializeMagick( exePath );

        MagickCore::MagickCoreGenesis( NULL, MagickFalse );

	// we do this to init the coder list, but will use it
	// more seriously in the future when we actually build up
	// the list of support modules dynamically!
	try {
	    std::list<CoderInfo> coderList;
		coderInfoList( &coderList, CoderInfo::TrueMatch, CoderInfo::AnyMatch, CoderInfo::AnyMatch);
	}
	catch(Exception e) {
	    e.what();
	};

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	pMainFrame->DragAcceptFiles();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}