// ================================================================================================
// Run!
// ================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    HWND hwnd;
    HBITMAP hBitmap;
    HDC hdc;
    unsigned long *rawBits = NULL;

    Register(hInstance);
    hi = hInstance;

    SetCursorPos(0, 0);

    totblt.QuadPart = 0;
    totrev.QuadPart = 0;
    totmemcpy.QuadPart = 0;


    // ------------------------------------------------------------------------------------------------
    // Create a window
    // ------------------------------------------------------------------------------------------------
    {
        hwnd = ::CreateWindowEx(WS_EX_TOPMOST, "BltTest", "", WS_POPUP | WS_EX_TOOLWINDOW,
                                256, 16, kWidth, kHeight,
                                (HWND)NULL, (HMENU)NULL, hInstance, LPVOID(NULL));

        ::ShowWindow((HWND)hwnd, SW_SHOWNORMAL);

        if (!hwnd) {
            MessageBox(NULL, TEXT("unable to create window?"), NULL, MB_OK);
            return -1;

        }
    }

    // ------------------------------------------------------------------------------------------------'
    // Create a checker-board bitmap
    // ------------------------------------------------------------------------------------------------
    {
        BITMAPINFO bmi;
        int bmihsize = sizeof(BITMAPINFOHEADER);
        memset(&bmi, 0, bmihsize);

        BITMAPINFOHEADER &h = bmi.bmiHeader;

        h.biSize		= bmihsize;
        h.biWidth		= kWidth;
        h.biHeight		= -kHeight;
        h.biPlanes		= 1;
        h.biBitCount	= 32;
        h.biCompression	= BI_RGB;

        hdc = CreateCompatibleDC(NULL);
        hBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&rawBits, NULL, 0);

        if (!hdc || !hBitmap) return -1;
    }

    // ------------------------------------------------------------------------------------------------
    // Simple contents
    // ------------------------------------------------------------------------------------------------
    for (int y = 0; y < kHeight; y++) {
        unsigned long *p0 = rawBits + kWidth * y;
        for (int x = 0; x < kWidth; x++) {
            unsigned long g = (x ^ y) & 0xFF;
            p0[x] = (g << 16) + (g << 8) + g;
        }
    }

    // make the capture from window look like a chess board

    HDC dc = (HDC)GetDC(hwnd);
    HBITMAP oldbitmap = (HBITMAP)SelectObject((HDC)hdc, hBitmap);
    ::BitBlt(dc, 0, 0, kWidth, kHeight, (HDC)hdc, 0, 0, SRCCOPY);
    SelectObject((HDC)hdc, oldbitmap);
    DeleteDC(dc);
    ::GdiFlush();

    // ------------------------------------------------------------------------------------------------
    // main loop
    // ------------------------------------------------------------------------------------------------
    for (int framecount = 0; framecount < kFramesBlt + kFramesRev + kFramesWithMemCpy; framecount++) {

        int result = 1;
        MSG msg;

        while (result) {
            result = PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE);

            if (result != 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // Message dispatching done, so draw a frame and measure timing
        LARGE_INTEGER s1, s2;
        QueryPerformanceCounter(&s1);

        if (framecount < kFramesBlt) {
            // from the desktop
            HDC dc = GetDC(NULL); // desktop HWND //HDC dc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
            ::CaptureDC(hBitmap, dc);
        } else if (framecount < (kFramesBlt + kFramesRev)) {
            // from the window
            HDC dc = (HDC)GetDC(hwnd);
            ::CaptureDC(hBitmap, dc);
        } else {
            HDC dc = GetDC(NULL);
            ::CaptureDC(hBitmap, dc);
        }

        QueryPerformanceCounter(&s2);
        LARGE_INTEGER diff;
        diff.QuadPart = s2.QuadPart - s1.QuadPart;

        if (framecount < kFramesBlt) {
            if (diff.QuadPart < minblt) minblt = diff.QuadPart;
            if (diff.QuadPart > maxblt) maxblt = diff.QuadPart;
            totblt.QuadPart += s2.QuadPart - s1.QuadPart;
        } else if (framecount < (kFramesBlt + kFramesRev)) {
            if (diff.QuadPart < minrev) minrev = diff.QuadPart;
            if (diff.QuadPart > maxrev) maxrev = diff.QuadPart;
            totrev.QuadPart += s2.QuadPart - s1.QuadPart;
        } else {
            totmemcpy.QuadPart += s2.QuadPart - s1.QuadPart;
        }
    }

    ::DestroyWindow(hwnd);
    ::DialogBoxParam(hi, MAKEINTRESOURCE(IDD_RESULTS), NULL, DlgProc, NULL);

    return 0;
}