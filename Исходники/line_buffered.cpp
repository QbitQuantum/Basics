//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId;
    int wmEvent;
    
    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 
            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_ABOUT:
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;

        case WM_ERASEBKGND:
            return 1;

        case WM_PAINT:
            // Let's open some theme data, and using BufferedPainting draw different fonts on glass background
            {
                RECT rcClient;
                GetClientRect(hWnd, &rcClient);

                MARGINS marGlassInset = {-1, -1, -1, -1}; // -1 means the whole window
                DwmExtendFrameIntoClientArea(hWnd, &marGlassInset);

                PAINTSTRUCT ps;
                HDC    hdc    = BeginPaint(hWnd, &ps);
                // ControlPanelStyle is declared in AeroStyle.xml
                HTHEME hTheme = OpenThemeData(NULL, L"ControlPanelStyle"); 

                if (hTheme)
                {
                    HDC hdcPaint = NULL;

                    BP_PAINTPARAMS params = { sizeof(BP_PAINTPARAMS) };
                    params.dwFlags        = BPPF_ERASE;

                    HPAINTBUFFER hBufferedPaint = BeginBufferedPaint(hdc, &rcClient, BPBF_TOPDOWNDIB, &params, &hdcPaint);
                    if (hdcPaint)
                    {
                        // Let's start with the simplest GDI default font
                        DTTOPTS DttOpts = {sizeof(DTTOPTS)};
                        DttOpts.dwFlags = DTT_COMPOSITED;
                        DrawText(hdcPaint, L"This is some GDI text in the default font", -1, &rcClient, 0);

                        // Let's look at the same text in the default theme
                        rcClient.top += RECT_INCREMENT;
                        DrawThemeTextEx(hTheme, hdcPaint, 0, 0, L"This is some text in the default font", -1, 0, &rcClient, &DttOpts);

                        // Let's add some text color to add to theming attributes and draw again
                        rcClient.top    += RECT_INCREMENT;
                        DttOpts.dwFlags |= DTT_TEXTCOLOR;
                        DttOpts.crText   = RGB(255, 255, 255);
                        // CPANEL_TASKLINK is declared in VSStyle.h
                        DrawThemeTextEx(hTheme, hdcPaint, CPANEL_TASKLINK, 0, L"This is some text in a themed font", -1, 0, &rcClient, &DttOpts);

                        // Draw text on glass in a selected font
                        DttOpts.dwFlags &= ~DTT_TEXTCOLOR;
                        LOGFONT lgFont;
                        HFONT hFontOld = NULL;
                        if (SUCCEEDED(GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont)))
                        {
                            HFONT hFont = CreateFontIndirect(&lgFont);
                            hFontOld    = (HFONT) SelectObject(hdcPaint, hFont);
                        }

                        rcClient.top += RECT_INCREMENT;
                        DrawText(hdcPaint, L"This is some GDI text in the selected font", -1, &rcClient, 0);

                        // The same selected font in themed text
                        rcClient.top += RECT_INCREMENT;
                        DrawThemeTextEx(hTheme, hdcPaint, 0, 0, L"This is some text in the selected font", -1, 0, &rcClient, &DttOpts);

                        SelectObject(hdcPaint, hFontOld);
                        rcClient.top += RECT_INCREMENT;
                        DrawText(hdcPaint, L"This is some GDI text in the default font", -1, &rcClient, 0);

                        // Let's add glow to our text attributes
                        DttOpts.dwFlags |= DTT_GLOWSIZE;
                        DttOpts.iGlowSize = 12; // Default value
                        // CompositedWindow::Window is declared in AeroStyle.xml
                        HTHEME hThemeWindow = OpenThemeData(NULL, L"CompositedWindow::Window");
                        if (hThemeWindow != NULL)
                        {
                            GetThemeInt(hThemeWindow, 0, 0, TMT_TEXTGLOWSIZE, &DttOpts.iGlowSize);
                            CloseThemeData(hThemeWindow);
                        }

                        rcClient.top += RECT_INCREMENT;
                        DrawThemeTextEx(hTheme, hdcPaint, 0, 0, L"This is some text with glow in the default font", -1, 0, &rcClient, &DttOpts);

                        // Now some color(theme) and glow
                        DttOpts.dwFlags |= DTT_TEXTCOLOR;
                        DttOpts.crText   = RGB(255, 255, 255);

                        rcClient.top += RECT_INCREMENT;
                        // CPANEL_TASKLINK is declared in VSStyle.h
                        DrawThemeTextEx(hTheme, hdcPaint, CPANEL_TASKLINK, 0, L"This is some text with glow in a themed font", -1, 0, &rcClient, &DttOpts);

                        DttOpts.dwFlags &= ~DTT_TEXTCOLOR;

                        // Find a particular font and draw using this
                        if (SUCCEEDED(GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont)))
                        {
                            HFONT hFont = CreateFontIndirect(&lgFont);
                            hFontOld    = (HFONT) SelectObject(hdcPaint, hFont);
                        }
                        
                        rcClient.top += RECT_INCREMENT;
                        DrawText(hdcPaint, L"This is some GDI text in the selected font", -1, &rcClient, 0);
                        
                        rcClient.top += RECT_INCREMENT;
                        DrawThemeTextEx(hTheme, hdcPaint, 0, 0, L"This is some text with glow in the selected font", -1, 0, &rcClient, &DttOpts);
                        
                        if (hFontOld)
                        {                        
                            SelectObject(hdcPaint, hFontOld);
                        }
                        EndBufferedPaint(hBufferedPaint, TRUE);
                    }
                    CloseThemeData(hTheme);
                }
                EndPaint(hWnd, &ps);
            }
            break;
        
        case WM_DESTROY:
            PostQuitMessage(0);
            BufferedPaintUnInit();
            break;
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}