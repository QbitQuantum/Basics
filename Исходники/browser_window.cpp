void BrowserWindow::OnSize() {
    if (cefBrowser_) {
        HWND browserHandle = cefBrowser_->GetHost()->GetWindowHandle();
        _ASSERT(browserHandle);
        RECT rect;
        GetClientRect(windowHandle_, &rect);
        HDWP hdwp = BeginDeferWindowPos(2);
        hdwp = DeferWindowPos(hdwp, browserHandle, NULL,
                rect.left, rect.top,
                rect.right - rect.left,
                rect.bottom - rect.top,
                SWP_NOZORDER);
        EndDeferWindowPos(hdwp);
    } else {
        LOG_DEBUG << "BrowserWindow::OnSize(): "
                       "CefBrowser object not yet created";
    }
}