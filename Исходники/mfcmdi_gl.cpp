BOOL CMfcmdi_glApp::InitInstance()
{
    AfxEnableControlContainer();

    // 標準的な初期化処理
    // もしこれらの機能を使用せず、実行ファイルのサイズを小さく
    // したければ以下の特定の初期化ルーチンの中から不必要なもの
    // を削除してください。

#ifdef _AFXDLL
    Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
    Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif

    // 設定が保存される下のレジストリ キーを変更します。
    // TODO: この文字列を、会社名または所属など適切なものに
    // 変更してください。
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    LoadStdProfileSettings();  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

    // アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
    //  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(
        IDR_MFCMDITYPE,
        RUNTIME_CLASS(CMfcmdi_glDoc),
        RUNTIME_CLASS(CChildFrame), // カスタム MDI 子フレーム
        RUNTIME_CLASS(CMfcmdi_glView));
    AddDocTemplate(pDocTemplate);

    // メイン MDI フレーム ウィンドウを作成
    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    m_pMainWnd = pMainFrame;

    // DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // コマンドラインでディスパッチ コマンドを指定します。
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // メイン ウィンドウが初期化されたので、表示と更新を行います。
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();

    return TRUE;
}