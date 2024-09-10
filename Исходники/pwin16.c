BOOL FAR PASCAL MGetWindowOrg(HDC hdc, INT FAR * px, INT FAR * py)
{
    DWORD dwSize;

    dwSize = GetWindowOrgEx(hdc);
    if (px != NULL) *px = (INT)LOWORD(dwSize);
    if (py != NULL) *py = (INT)HIWORD(dwSize);

    return(TRUE);
}