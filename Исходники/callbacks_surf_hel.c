DWORD CALLBACK HelDdSurfUnlock(LPDDHAL_UNLOCKDATA lpUnLockData)
{
    HDC hDC;
    HBITMAP hImage = NULL;

    HDC hMemDC = NULL;
    HBITMAP hDCBmp = NULL;
    BITMAP bm = {0};

    DX_WINDBG_trace();

    /* Get our hdc for the active window */
    hDC = GetDC((HWND)lpUnLockData->lpDDSurface->lpSurfMore->lpDD_lcl->hFocusWnd);

    if (hDC != NULL)
    {
        /* Create a memory bitmap to store a copy of current hdc surface */

        /* fixme the rcarea are not store in the struct yet so the data will look corupted */
        hImage = CreateCompatibleBitmap (hDC, lpUnLockData->lpDDSurface->lpGbl->wWidth, lpUnLockData->lpDDSurface->lpGbl->wHeight);

        /* Create a memory hdc so we can draw on our current memory bitmap */
        hMemDC = CreateCompatibleDC(hDC);

        if (hMemDC != NULL)
        {
            /* Select our memory bitmap to our memory hdc */
            hDCBmp = (HBITMAP) SelectObject (hMemDC, hImage);

            /* Get our memory bitmap information */
            GetObject(hImage, sizeof(BITMAP), &bm);

            SetBitmapBits(hImage,bm.bmWidthBytes * bm.bmHeight, lpUnLockData->lpDDSurface->lpSurfMore->lpDDRAWReserved2);

            BitBlt (hDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);

            SelectObject (hMemDC, hDCBmp);

            /* Setup return value */
             lpUnLockData->ddRVal = DD_OK;
        }
    }

    /* Cleanup after us */
    if (hImage != NULL)
    {
        DeleteObject (hImage);
    }

    if (hMemDC != NULL)
    {
        DeleteDC (hMemDC);
    }

    if (lpUnLockData->lpDDSurface->lpSurfMore->lpDDRAWReserved2 != NULL)
    {
        HeapFree(GetProcessHeap(), 0, lpUnLockData->lpDDSurface->lpSurfMore->lpDDRAWReserved2 );
    }

    return DDHAL_DRIVER_HANDLED;
}