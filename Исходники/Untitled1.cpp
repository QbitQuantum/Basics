LRESULT _stdcall WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HDC hDC = GetWindowDC(hWnd);
    static HRGN hRgn = CreateRectRgn(120, 70, 280, 230);

    switch(uMsg)
    {
    case WM_ERASEBKGND:
         {
             DefWindowProc(hWnd, uMsg, wParam, lParam);
             FillRgn(hDC, hRgn, CreateSolidBrush(RGB(255, 165, 0))); // Orange
             SelectObject(hDC, hRgn);
             return 0;
         }

     case WM_CREATE:
         {
             HRGN hRgn1 = CreateEllipticRgn(0, 0, 400, 300);
             HRGN hRgn2 = CreateEllipticRgn(150, 100, 250, 200);
             CombineRgn(hRgn1, hRgn1, hRgn2, RGN_XOR);
             SetWindowRgn(hWnd, hRgn1, TRUE);
             DeleteObject(hRgn1);
             DeleteObject(hRgn2);
             break;
         }

     case WM_LBUTTONDOWN:
         {
             SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
             break;
         }

     case WM_DESTROY:
         {
             DeleteObject(hRgn);
             ReleaseDC(hWnd, hDC);
             PostQuitMessage(0);
             break;
         }
     }
     return DefWindowProc(hWnd, uMsg, wParam, lParam);;
 }