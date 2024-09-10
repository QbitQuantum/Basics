static IntSize getWebViewSize(WebView& webView)
{
    RECT r;
    webView.frameRect(&r);
    return IntSize(r.right - r.left, r.bottom - r.top);
}