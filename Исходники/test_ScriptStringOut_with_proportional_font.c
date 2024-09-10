LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    WCHAR sometext[] = {'C','h','i','n','a','1','2','3',0};
    int len = (sizeof(sometext) / sizeof(WCHAR)) - 1;
    RECT rc = {0, 0, 100, 100};
    SCRIPT_STRING_ANALYSIS ssa = NULL;
    HFONT hFont;

    switch (message)
    {
        case WM_CREATE:
            return 0;

        case WM_COMMAND:
            break;

        case WM_PAINT:
            BeginPaint(hwnd, &ps);

            hdc = GetDC(hwnd);
            hFont = CreateFontA(-32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Hiragino Sans GB W3");
            SelectObject(hdc, hFont);
            ScriptStringAnalyse(hdc, sometext, len, len * 2, -1, SSA_GLYPHS|SSA_FALLBACK, 0,
                                     NULL, NULL, NULL, NULL, NULL, &ssa);
            ScriptStringOut(ssa, 10, 10, 0, &rc, 0, 0, FALSE);
            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}