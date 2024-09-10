DrawEngine::DrawEngine(HDC hdc, HWND hwnd, int pxPerBlock,
                       int width, int height) :
    hdc(hdc), hwnd(hwnd), width(width), height(height)
{
    GetClientRect(hwnd, &rect);

    SaveDC(hdc);

    // Set up coordinate system
    SetMapMode(hdc, MM_ISOTROPIC);
    SetViewportExtEx(hdc, pxPerBlock, pxPerBlock, 0);
    SetWindowExtEx(hdc, 1, -1, 0);
    SetViewportOrgEx(hdc, 0, rect.bottom, 0);

    // Set default colors
    SetTextColor(hdc, RGB(255,255,255));
    SetBkColor(hdc, RGB(70,70,70));
    SetBkMode(hdc, TRANSPARENT);
}