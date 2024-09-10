BOOL CSimpViewApp::InitInstance()
{
    RandomParam::init();

    CMDIFrameWnd* pFrame = new CMainFrame;
    m_pMainWnd = pFrame;

    // Create main MDI frame window
    if (!pFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;

    // Load shared MDI menus and accelerator table
    HINSTANCE hInst = AfxGetResourceHandle();
    m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_STEP1_VIEW));
    m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_STEP1_VIEW));

    pFrame->ShowWindow(m_nCmdShow);
    pFrame->UpdateWindow();
    pFrame->PostMessage(WM_COMMAND, ID_FILE_NEW);

    return TRUE;
}