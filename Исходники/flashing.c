LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {
  
    FLASHWINFO fwi;

    switch(msg)  {
    
      case WM_CREATE:

          CreateWindowW(L"Button", L"Flash",
                  WS_CHILD | WS_VISIBLE,
                  10, 10, 80, 25, 
                  hwnd, (HMENU) 1, NULL, NULL);
          break;

      case WM_COMMAND:

          fwi.cbSize = sizeof(fwi);
          fwi.dwFlags = FLASHW_ALL;
          fwi.dwTimeout = 0;
          fwi.hwnd = hwnd;
          fwi.uCount = 4;

          FlashWindowEx(&fwi);
          break;

      case WM_DESTROY:

          PostQuitMessage(0);
          break; 
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}