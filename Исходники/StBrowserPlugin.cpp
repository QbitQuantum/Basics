LRESULT StBrowserPlugin::stWndProc(HWND   theWnd,
                                   UINT   theMsg,
                                   WPARAM theParamW,
                                   LPARAM theParamL) {
    if(theMsg == WM_ERASEBKGND) {
        return 1;
    } else if(theMsg == WM_PAINT
              && !myIsActive) {
        RECT aRect;
        GetClientRect(theWnd, &aRect);
        HDC aDevCtx = GetDC(theWnd);
        FillRect(aDevCtx, &aRect, myBackBrush);
        ReleaseDC(theWnd, aDevCtx);
        return 0;
    }

    return CallWindowProcW(myProcOrig, theWnd, theMsg, theParamW, theParamL);
}