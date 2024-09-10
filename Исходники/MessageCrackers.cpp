void OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags)
{
    HDC hdc = GetDC(hWnd); 
    SetPixel(hdc, x, y, RGB(255,0,0)); 
    ReleaseDC(hWnd, hdc);
}