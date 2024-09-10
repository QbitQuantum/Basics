CFrameWorkApp::CFrameWorkApp()
{
    uintptr_t hThread = _beginthread(framework_main_thread,0,0);
};