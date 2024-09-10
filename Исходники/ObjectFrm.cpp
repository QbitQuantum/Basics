int CObjectFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    CMDIFrameWnd *mainWnd;
    RECT rectMain;

    // Register the doc templates we provide to the app
    CWinApp* pApp = AfxGetApp();
    ASSERT(pApp != NULL);
    mainWnd = DYNAMIC_DOWNCAST(CMDIFrameWnd, pApp->m_pMainWnd);

    // get the apps instance handle for loading resources
    m_AppInst = AfxGetResourceHandle();
    // now tell the application to look in dll for resources
    AfxSetResourceHandle(ObjectEditorDLL.hModule);

    mainWnd->GetClientRect(&rectMain);

    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;


    AfxSetResourceHandle(m_AppInst);

    return 0;
}