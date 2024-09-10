int CLightTexApp::Run() {
    HWND hwnd = m_pMainWnd->GetSafeHwnd();
    BOOL windowed = TRUE;
    auto_ptr<RenderLightTex> render(new RenderLightTex());
    if (!render->Init(WIN_WIDTH, WIN_HEIGHT, hwnd, windowed, D3DDEVTYPE_HAL)) {
        m_pMainWnd->MessageBox(_T("Initialize render failed."), _T("Error"), MB_OK | MB_ICONERROR);
        return Exit(-1);
    }

    auto_ptr<LightTexInput> input(new LightTexInput());
    m_GameMain.reset(new SGL::Main());
    m_GameMain->Init(render.get(), input.get());

    // 调整窗口大小
    CMainFrame* pFrmWnd = (CMainFrame*) m_pMainWnd;
    pFrmWnd->SetGameMain(m_GameMain.get());
    if (windowed)
        m_GameMain->AdjustWindowed(pFrmWnd->GetStyle(), pFrmWnd->GetExStyle(), pFrmWnd->GetMenu()->GetSafeHmenu());
    else
        m_GameMain->AdjustFullscreen();

    // 更新窗口显示
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    // 消息循环
    int exitCode = m_GameMain->StartLoop(SGL::MFCIdle, SGL::MFCPreTransMessage);

    // 按照约定重载 Run 应手工调用 ExitInstance
    return Exit(exitCode);
}