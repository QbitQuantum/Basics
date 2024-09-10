HWND WINAPI HookCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    RECT    rcWordArea;
    ULONG   Length;
    LPWSTR  ClassName, WindowName;
    HWND    hWnd;

    Length = StrLengthA(lpClassName) + 1;
    ClassName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    AnsiToUnicode(ClassName, Length * sizeof(WCHAR), lpClassName, Length);

    Length = StrLengthA(lpWindowName) + 1;
    WindowName = (LPWSTR)AllocStack(Length * sizeof(WCHAR));
    AnsiToUnicode(WindowName, Length * sizeof(WCHAR), lpWindowName, Length);

    hWnd = CreateWindowExW(dwExStyle, ClassName, WindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (hWnd == NULL)
        return hWnd;

    OrigWndProc = (WNDPROC)SetWindowLongPtrA(hWnd, GWLP_WNDPROC, (LONG_PTR)CMVS_MainWindowProc);
    DragAcceptFiles(hWnd, TRUE);

    return hWnd;
}