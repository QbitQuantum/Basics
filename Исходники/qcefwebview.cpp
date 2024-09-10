void QCefWebView::ResizeBrowser(const QSize& size) {
    if (qcef_client_handler.get() && qcef_client_handler->GetBrowser()) {
        CefWindowHandle hwnd =
                qcef_client_handler->GetBrowser()->GetHost()->GetWindowHandle();
        if (hwnd) {
            HDWP hdwp = BeginDeferWindowPos(1);
            hdwp = DeferWindowPos(hdwp, hwnd, NULL,
                                  0, 0, size.width(), size.height(),
                                  SWP_NOZORDER);
            EndDeferWindowPos(hdwp);
        }
    }
}