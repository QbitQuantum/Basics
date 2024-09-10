int CID3DXFontApp::Run()
{
    HWND hwnd = m_pMainWnd->GetSafeHwnd();
    BOOL windowed = TRUE;
    auto_ptr<RenderID3DXFont> render(new RenderID3DXFont());
    if (!render->Init(WIN_WIDTH, WIN_HEIGHT, hwnd, windowed, D3DDEVTYPE_HAL))
        return Exit(-1);

    auto_ptr<ID3DXFontInput> input(new ID3DXFontInput());
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
    int exitCode = 0;
    exitCode = m_GameMain->StartLoop(SGL::MFCIdle, SGL::MFCPreTransMessage);

    // NOTE: 按照约定应调用 ExitInstance, 重载 Run 时, 不自动调用 ExitInstance
    return Exit(exitCode);
}