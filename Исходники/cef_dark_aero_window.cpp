// Setup the device context for drawing
void cef_dark_aero_window::InitDeviceContext(HDC hdc)
{
    if (CanUseAeroGlass()) {
        RECT rectClipClient;
        SetRectEmpty(&rectClipClient);
        GetRealClientRect(&rectClipClient);

        // exclude the client area to reduce flicker
        ::ExcludeClipRect(hdc, rectClipClient.left, rectClipClient.top, rectClipClient.right, rectClipClient.bottom);
    } else {
        cef_dark_window::InitDeviceContext(hdc);
    }
}