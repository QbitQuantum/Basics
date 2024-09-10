static VOID
Run(VOID)
{
    HWND hDesktopWnd;
    HDC hdcDesktop, hdcMem;

    /* Get the screen size */
    g_pInfo->cx = GetSystemMetrics(SM_CXSCREEN);
    g_pInfo->cy = GetSystemMetrics(SM_CYSCREEN);

    hDesktopWnd = GetDesktopWindow();

    /* Get the DC for the desktop */
    hdcDesktop = GetDCEx(hDesktopWnd, NULL, DCX_CACHE);
    if (hdcDesktop)
    {
        /* Initialize the base background onto a DC */
        hdcMem = DrawBaseBackground(hdcDesktop);
        if (hdcMem)
        {
            /* TEST : Draw logoff screen */
            DrawLogoffScreen(hdcMem);

            /* Blit the off-screen DC to the desktop */
            BitBlt(hdcDesktop,
                   0,
                   0,
                   g_pInfo->cx,
                   g_pInfo->cy,
                   hdcMem,
                   0,
                   0,
                   SRCCOPY);

            /* Delete the memory DC */
            DeleteDC(hdcMem);
        }

        /* Release the desktop DC */
        ReleaseDC(hDesktopWnd, hdcDesktop);
    }
}