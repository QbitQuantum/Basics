LRESULT MetroWindow::InitializeWindow()
{
    HMONITOR hMonitor;
    POINT    pt;
    UINT     dpix = 0, dpiy = 0;
    HRESULT  hr = E_FAIL;

    // Get the DPI for the main monitor, and set the scaling factor
    pt.x = 1;
    pt.y = 1;
    hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    hr = GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpix, &dpiy);

    if (hr != S_OK) {
        ::MessageBox(NULL, (LPCWSTR)L"GetDpiForMonitor failed", (LPCWSTR)L"Notification", MB_OK);
        return FALSE;
    }
    g_Dpi->SetScale(dpix);
    RECT layout = { g_Dpi->Scale(100), g_Dpi->Scale(100), g_Dpi->Scale(720), g_Dpi->Scale(540) };
    Create(nullptr, layout, L"PE File Analyzer",
           WS_NORESIZEWINDOW,
           WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
    return S_OK;
}