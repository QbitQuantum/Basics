/* The function makes the window visible if it is hidden
 or is not yet shown. */
void
SplashRedrawWindow(Splash * splash)
{
    if (!SplashIsStillLooping(splash)) {
        KillTimer(splash->hWnd, 0);
    }

    if (splash->currentFrame < 0) {
        return;
    }

    SplashUpdateScreenData(splash);
    if (splash->isLayered) {
        BLENDFUNCTION bf;
        POINT ptSrc;
        HDC hdcSrc = CreateCompatibleDC(NULL), hdcDst;
        BITMAPINFOHEADER bmi;
        void *bitmapBits;
        HBITMAP hBitmap, hOldBitmap;
        RECT rect;
        POINT ptDst;
        SIZE size;

        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.AlphaFormat = AC_SRC_ALPHA;
        bf.SourceConstantAlpha = 0xFF;
        ptSrc.x = ptSrc.y = 0;

        memset(&bmi, 0, sizeof(bmi));
        bmi.biSize = sizeof(BITMAPINFOHEADER);
        bmi.biWidth = splash->width;
        bmi.biHeight = -splash->height;
        bmi.biPlanes = 1;
        bmi.biBitCount = 32;
        bmi.biCompression = BI_RGB;

        //      FIXME: this is somewhat ineffective
        //      maybe if we allocate memory for all frames as DIBSections,
        //      then we could select the frames into the DC directly

        hBitmap = CreateDIBSection(NULL, (BITMAPINFO *) & bmi, DIB_RGB_COLORS,
                &bitmapBits, NULL, 0);
        memcpy(bitmapBits, splash->screenData,
                splash->screenStride * splash->height);
        hOldBitmap = (HBITMAP) SelectObject(hdcSrc, hBitmap);
        hdcDst = GetDC(splash->hWnd);

        GetWindowRect(splash->hWnd, &rect);

        ptDst.x = rect.left;
        ptDst.y = rect.top;

        size.cx = splash->width;
        size.cy = splash->height;

        UpdateLayeredWindow(splash->hWnd, hdcDst, &ptDst, &size,
                hdcSrc, &ptSrc, 0, &bf, ULW_ALPHA);

        ReleaseDC(splash->hWnd, hdcDst);
        SelectObject(hdcSrc, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hdcSrc);
    }
    else {
       InvalidateRect(splash->hWnd, NULL, FALSE);
       if (splash->maskRequired) {
            HRGN hRgn = CreateRectRgn(0, 0, 0, 0);

            CombineRgn(hRgn, splash->frames[splash->currentFrame].hRgn,
                    splash->frames[splash->currentFrame].hRgn, RGN_COPY);
            SetWindowRgn(splash->hWnd, hRgn, TRUE);
        } else {
            SetWindowRgn(splash->hWnd, NULL, TRUE);
        }
        UpdateWindow(splash->hWnd);
    }
    if (!IsWindowVisible(splash->hWnd)) {
        POINT cursorPos;
        ShowWindow(splash->hWnd, SW_SHOW);
        // Windows won't update the cursor after the window is shown,
        // if the cursor is already above the window. need to do this manually.
        GetCursorPos(&cursorPos);
        if (WindowFromPoint(cursorPos) == splash->hWnd) {
            // unfortunately Windows fail to understand that the window
            // thread should own the cursor, even though the mouse pointer
            // is over the window, until the mouse has been moved.
            // we're using SetCursorPos here to fake the mouse movement
            // and enable proper update of the cursor.
            SetCursorPos(cursorPos.x, cursorPos.y);
            SetCursor(LoadCursor(NULL, IDC_WAIT));
        }
    }
    if (SplashIsStillLooping(splash)) {
        int time = splash->time +
            splash->frames[splash->currentFrame].delay - SplashTime();

        if (time < 0)
            time = 0;
        SetTimer(splash->hWnd, 0, time, NULL);
    }
}