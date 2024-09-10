static LONG WINAPI handle(HWND win, UINT msg, WPARAM w, LPARAM l) {
        LONG r;
        switch (msg) {
#define HANDLE(x) case WM_##x: cvReport("han " #x); r = HANDLE_WM_##x(win, w, l, on##x); break
                HANDLE(TIMER);
                HANDLE(PAINT);
                HANDLE(MOUSEMOVE);
                HANDLE(SIZE);
                HANDLE(KEYDOWN);
                HANDLE(SYSKEYDOWN);
                HANDLE(SYSKEYUP);
                HANDLE(CHAR);
                HANDLE(KEYUP);
                HANDLE(LBUTTONDOWN);
                HANDLE(RBUTTONDOWN);
                HANDLE(MBUTTONDOWN);
                HANDLE(LBUTTONUP);
                HANDLE(RBUTTONUP);
                HANDLE(MBUTTONUP);
                HANDLE(MOUSEWHEEL);
                HANDLE(DESTROY);
                HANDLE(CLOSE);
#undef HANDLE
        case WM_IME_STARTCOMPOSITION: {
                HIMC imc = ImmGetContext(win);
                COMPOSITIONFORM cf;
                cf.dwStyle = CFS_POINT;
                cf.ptCurrentPos.x = cvMouseX();
                cf.ptCurrentPos.y = cvMouseY();
                ImmSetCompositionWindow(imc, &cf);
                ImmReleaseContext(win, imc);
                r = 1;
        }
        break;
        case WM_IME_COMPOSITION: {
                if(l & GCS_RESULTSTR){
                        unsigned short str[4096];
                        unsigned len, i; 
                        HIMC imc = ImmGetContext(win);
                        HDC dc = GetDC(win);
                        len = ImmGetCompositionString(imc, GCS_RESULTSTR, str, sizeof(str));
                        len >>= 1;
                        for (i = 0; i < len; i++)
                                wgot(win, CVE_UNICODE, str[i], 0); 
                        ImmReleaseContext(win, imc);
                        chk(ReleaseDC(win, dc));
                }
                r = 0;
        }
        break;
        default: r = 0;
        }