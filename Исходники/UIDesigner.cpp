BOOL CUIDesignerApp::InitInstance()
{
    // 如果一个运行在 Windows XP 上的应用程序清单指定要
    // 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
    //则需要 InitCommonControlsEx()。否则，将无法创建窗口。
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // 将它设置为包括所有要在应用程序中使用的
    // 公共控件类。
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinAppEx::InitInstance();

    // 初始化 OLE 库
    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }
    AfxEnableControlContainer();
    // 标准初始化
    // 如果未使用这些功能并希望减小
    // 最终可执行文件的大小，则应移除下列
    // 不需要的特定初始化例程
    // 更改用于存储设置的注册表项
    // TODO: 应适当修改该字符串，
    // 例如修改为公司或组织名
    SetRegistryKey(_T(""));
    LoadStdProfileSettings();  // 加载标准 INI 文件选项(包括 MRU)
    SetRegistryBase(_T("Settings"));

    InitContextMenuManager();

    InitKeyboardManager();

    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
            RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    // 注册应用程序的文档模板。文档模板
    // 将用作文档、框架窗口和视图之间的连接

    CMultiDocTemplate* pUIDocTemplate = NULL;
    pUIDocTemplate = new CMultiDocTemplate(IDR_UIDESIGNER,
                                           RUNTIME_CLASS(CUIDesignerDoc),
                                           RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
                                           RUNTIME_CLASS(CUIDesignerView));
    if (!pUIDocTemplate)
        return FALSE;
    AddDocTemplate(pUIDocTemplate);

    // 创建主 MDI 框架窗口
    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        delete pMainFrame;
        return FALSE;
    }
    m_pMainWnd = pMainFrame;
    // 仅当具有后缀时才调用 DragAcceptFiles
    //  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生
    // 启用拖/放
    m_pMainWnd->DragAcceptFiles();

    // 启用“DDE 执行”
    EnableShellOpen();
    RegisterShellFileTypes(TRUE);

    // 主窗口已初始化，因此显示它并对其进行更新
    pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
    pMainFrame->UpdateWindow();

    return TRUE;
}