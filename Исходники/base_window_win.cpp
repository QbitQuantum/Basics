void WindowWin::WindowResize(unsigned int iWidth, unsigned int iHeight)
{
    if(!m_bWndCreated)
        return;

    if(m_bFullscreen)
        return;

    ::RECT workArea;
    WINDOWINFO info;
    unsigned int iDescWidth;
    unsigned int iDescHeight;
    info.cbSize = sizeof(WINDOWINFO);
    GetWindowInfo(m_hWnd, &info);

    // Get work area (without taskbar and other toolbars)
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    iDescWidth  = workArea.right - workArea.left;
    iDescHeight = workArea.bottom - workArea.top;

    // compensate for window border
    if(info.cxWindowBorders && info.cyWindowBorders)
    {
        iWidth  = iWidth + (info.rcClient.left - info.rcWindow.left) + (info.rcWindow.right - info.rcClient.right);
        iHeight = iHeight + (info.rcClient.top - info.rcWindow.top) + (info.rcWindow.bottom - info.rcClient.bottom);
    }

    // shift window if too large
    if(iWidth > iDescWidth)
    {
        info.rcWindow.left = workArea.left;
        iWidth = iDescWidth;
    }
    else if((info.rcWindow.left + iWidth) > iDescWidth)
        info.rcWindow.left -= ((iWidth + info.rcWindow.left) - iDescWidth);
    else if(info.rcWindow.left < workArea.left)
        info.rcWindow.left = workArea.left;

    if(iHeight > iDescHeight)
    {
        info.rcWindow.top = workArea.top;
        iHeight = iDescHeight;
    }
    else if((info.rcWindow.top + iHeight) > iDescHeight)
        info.rcWindow.top -= ((iHeight + info.rcWindow.top) - iDescHeight);
    else if(info.rcWindow.top < workArea.top)
        info.rcWindow.top = workArea.top;

    m_wndRect.x      = info.rcWindow.left;
    m_wndRect.y      = info.rcWindow.top;
    m_wndRect.width  = iWidth;
    m_wndRect.height = iHeight;
    MoveWindow(m_hWnd, m_wndRect.x, m_wndRect.y, m_wndRect.width, m_wndRect.height, TRUE);
}