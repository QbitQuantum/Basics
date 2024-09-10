 virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
 {
     Vector p = vectorFromLParam(lParam);
     switch (uMsg) {
         case WM_LBUTTONDOWN:
             _lButtonDown = true;
             break;
         case WM_LBUTTONUP:
             _lButtonDown = false;
             releaseCapture();
             break;
         case WM_MBUTTONDOWN:
             _mButtonDown = true;
             break;
         case WM_MBUTTONUP:
             _mButtonDown = false;
             releaseCapture();
             break;
         case WM_RBUTTONDOWN:
             _rButtonDown = true;
             break;
         case WM_RBUTTONUP:
             _rButtonDown = false;
             releaseCapture();
             break;
         case WM_MOUSEMOVE:
             break;
         case WM_CHAR:
             break;
         case WM_KILLFOCUS:
             _capture = false;
             ReleaseCapture();
             break;
     }
     return WindowsWindow::handleMessage(uMsg, wParam, lParam);
 }