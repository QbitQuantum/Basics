// 程序入口.
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    HRESULT hRes = OleInitialize(NULL);

    // this resolves ATL window thunking problem when Microsoft Layer
    // for Unicode (MSLU) is used.
    ::DefWindowProc(NULL, 0, 0, 0L);

    base::EnableTerminationOnHeapCorruption();

    // 负责调用单件对象的析构函数.
    base::AtExitManager exit_manager;

    CommandLine::Init(0, NULL);

    FilePath res_dll;
    PathService::Get(base::DIR_EXE, &res_dll);
    res_dll = res_dll.Append(L"wanui_res.dll");
    ui::ResourceBundle::InitSharedInstance(res_dll);

    MessageLoop main_message_loop(MessageLoop::TYPE_UI);

    view::desktop::DesktopViewDelegate view_delegate;

    // 只支持纯view配置.
    view::Widget::SetPureViews(true);

    view::desktop::DesktopWindowView::CreateDesktopWindow(
        view::desktop::DesktopWindowView::DESKTOP_DEFAULT);
    view::desktop::DesktopWindowView::desktop_window_view->CreateTestWindow(
        L"Sample Window 1", SK_ColorWHITE, gfx::Rect(500, 200, 400, 400), true);
    view::desktop::DesktopWindowView::desktop_window_view->CreateTestWindow(
        L"Sample Window 2", SK_ColorRED, gfx::Rect(600, 450, 450, 300), false);

    view::AcceleratorHandler accelerator_handler;
    MessageLoopForUI::current()->Run(&accelerator_handler);

    ui::ResourceBundle::CleanupSharedInstance();
    OleUninitialize();

    return 0;
}