void Win32WebControl::lazyInit()
{
    // reset the main windows style so that its drawing does not cover the webview sub window
    HWND hwnd = cocos2d::Director::getInstance()->getOpenGLView()->getWin32Window();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style | WS_CLIPCHILDREN);

    HINSTANCE hInstance = GetModuleHandle(NULL);
    CoInitialize(NULL);
    s_module.Init(NULL, hInstance);
    AtlAxWinInit();
}