int WiEngineApp::runWithScene(wyScene* s) {
	// load accelerator table
	HACCEL hAccelTable = LoadAccelerators(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_WIENGINESKELETONPROJECT));

	// register window class
	registerWindowClass();

	// create window
	createWindow();

	// set window and accelerator to gl view
	m_glView->setWindowHandle(m_hWnd);
	m_glView->setAccelTable(hAccelTable);

	// show window
	showWindow();

	// prepare
	m_glView->prepare();

	// run with first scene
	wyDirector::getInstance()->runWithScene(s);

	// run
	return m_glView->run();
}