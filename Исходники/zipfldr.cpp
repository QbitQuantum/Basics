EXTERN_C
BOOL WINAPI
RouteTheCall(
    IN HWND hWndOwner,
    IN HINSTANCE hInstance,
    IN LPCSTR lpStringArg,
    IN INT Show)
{
    CStringW path = lpStringArg;
    PathRemoveBlanksW(path.GetBuffer());
    path.ReleaseBuffer();
    path = L"\"" + path + L"\"";
    ShellExecuteW(NULL, L"open", L"explorer.exe", path.GetString(), NULL, SW_SHOWNORMAL);
    return TRUE;
}