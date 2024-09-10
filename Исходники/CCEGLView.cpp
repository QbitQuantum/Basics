void CCEGLView::end()
{
    cleanup();

    UiApp* pApp = UiApp::GetInstance();
    AppAssert(pApp);
    pApp->Terminate();
}