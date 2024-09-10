 bool setTransparency(HWND hWnd, unsigned char alpha)
 {
     SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
     SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
     return true;
 }