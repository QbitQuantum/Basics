BOOL CTrayNotifyIcon::GetDynamicDCAndBitmap(CDC* pDC, CBitmap* pBitmap)
{
    //Validate our parameters
    ATLASSERT(pDC != NULL);
    ATLASSERT(pBitmap != NULL);

    //Get the HWND for the desktop
#ifdef _AFX
    CWnd* pWndScreen = CWnd::GetDesktopWindow();
    if (pWndScreen == NULL)
        return FALSE;
#else
    CWindow WndScreen(::GetDesktopWindow());
    if (!WndScreen.IsWindow())
        return FALSE;
#endif

    //Get the desktop HDC to create a compatible bitmap from
#ifdef _AFX
    CDC* pDCScreen = pWndScreen->GetDC();
    if (pDCScreen == NULL)
        return FALSE;
#else
    CDC DCScreen(WndScreen.GetDC());
    if (DCScreen.IsNull())
        return FALSE;
#endif

    //Get the width and height of a small icon
    int w = GetSystemMetrics(SM_CXSMICON);
    int h = GetSystemMetrics(SM_CYSMICON);

    //Create an off-screen bitmap that the dynamic tray icon
    //can be drawn into. (Compatible with the desktop DC).
#ifdef _AFX
    BOOL bSuccess = pBitmap->CreateCompatibleBitmap(pDCScreen, w, h);
#else
    BOOL bSuccess = (pBitmap->CreateCompatibleBitmap(DCScreen.operator HDC(), w, h) != NULL);
#endif
    if (!bSuccess)
    {
#ifdef _AFX
        pWndScreen->ReleaseDC(pDCScreen);
#else
        WndScreen.ReleaseDC(DCScreen);
#endif
        return FALSE;
    }

    //Get a HDC to the newly created off-screen bitmap
#ifdef _AFX
    bSuccess = pDC->CreateCompatibleDC(pDCScreen);
#else
    bSuccess = (pDC->CreateCompatibleDC(DCScreen.operator HDC()) != NULL);
#endif
    if (!bSuccess)
    {
        //Release the Screen DC now that we are finished with it
#ifdef _AFX
        pWndScreen->ReleaseDC(pDCScreen);
#else
        WndScreen.ReleaseDC(DCScreen);
#endif

        //Free up the bitmap now that we are finished with it
        pBitmap->DeleteObject();

        return FALSE;
    }

    //Select the bitmap into the offscreen DC
#ifdef _AFX
    pDC->SelectObject(pBitmap);
#else
    pDC->SelectBitmap(pBitmap->operator HBITMAP());
#endif

    //Release the Screen DC now that we are finished with it
#ifdef _AFX
    pWndScreen->ReleaseDC(pDCScreen);
#else
    WndScreen.ReleaseDC(DCScreen);
#endif

    return TRUE;
}