static LRESULT iewnd_OnCreate(HWND hwnd, LPCREATESTRUCTW lpcs)
{
    SetWindowLongPtrW(hwnd, 0, (LONG_PTR) lpcs->lpCreateParams);
    return 0;
}