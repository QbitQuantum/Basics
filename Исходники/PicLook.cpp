BOOL CPaintLibViewerApp::InitInstance()
{
    // Standard initialization
    SetRegistryKey( "PaintLib" );
    LoadStdProfileSettings(5);  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    ASSERT(m_pDocManager == NULL);
    m_pDocManager = new CDocManagerEx;
    CMultiDocTemplate* pDocTemplate;
    // BMP aware, and more ...
    pDocTemplate = new CMultiDocTemplate(
                       IDR_BMPTYPE,
                       RUNTIME_CLASS(CPLViewerDoc),
                       RUNTIME_CLASS(CMDIChildWnd),    // standard MDI child frame
                       //RUNTIME_CLASS(CChildFrame),    // derived MDI child frame
                       RUNTIME_CLASS(CPLView));
    m_pDocManager->AddDocTemplate(pDocTemplate);

    // create main MDI Frame window
    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
        return false;
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();
    m_pMainWnd = pMainFrame;

    // enable file manager drag/drop and DDE Execute open
    m_pMainWnd->DragAcceptFiles();

    // Uncomment this to have PicLook register itself as default viewer
    // for image files.
    // EnableShellOpen();
    // RegisterShellFileTypes(true);

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // MFC faq says this avoids 1st (empty) doc
    if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
        cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return false;

#ifdef _DEBUG
    PLPicDecoder::SetTraceConfig( 3, NULL );
#endif
    return true;
}