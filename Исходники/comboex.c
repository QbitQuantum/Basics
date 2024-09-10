static BOOL init(void)
{
    HMODULE hComctl32;
    BOOL (WINAPI *pInitCommonControlsEx)(const INITCOMMONCONTROLSEX*);
    WNDCLASSA wc;
    INITCOMMONCONTROLSEX iccex;

    hComctl32 = GetModuleHandleA("comctl32.dll");
    pInitCommonControlsEx = (void*)GetProcAddress(hComctl32, "InitCommonControlsEx");
    if (!pInitCommonControlsEx)
    {
        win_skip("InitCommonControlsEx() is missing. Skipping the tests\n");
        return FALSE;
    }
    iccex.dwSize = sizeof(iccex);
    iccex.dwICC  = ICC_USEREX_CLASSES;
    pInitCommonControlsEx(&iccex);

    pSetWindowSubclass = (void*)GetProcAddress(hComctl32, (LPSTR)410);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(NULL);
    wc.hIcon = NULL;
    wc.hCursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
    wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ComboExTestClass;
    wc.lpfnWndProc = ComboExTestWndProc;
    RegisterClassA(&wc);

    hComboExParentWnd = CreateWindowExA(0, ComboExTestClass, "ComboEx test", WS_OVERLAPPEDWINDOW|WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, 680, 260, NULL, NULL, GetModuleHandleA(NULL), 0);
    ok(hComboExParentWnd != NULL, "failed to create parent window\n");

    hMainHinst = GetModuleHandleA(NULL);

    return hComboExParentWnd != NULL;
}