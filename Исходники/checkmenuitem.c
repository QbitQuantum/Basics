LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {
    
    UINT state;

    switch(msg) {
    
      case WM_CREATE:
      
          AddMenus(hwnd);          
          InitCommonControls();

          ghSb = CreateWindowExW(0, STATUSCLASSNAMEW, NULL, 
              WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, 
              (HMENU) 1, GetModuleHandle(NULL), NULL);

          break;

      case WM_COMMAND:
          
          switch(LOWORD(wParam)) {
          
              case IDM_VIEW_STB:                                    
                  
                  state = GetMenuState(ghMenu, IDM_VIEW_STB, MF_BYCOMMAND); 

                  if (state == MF_CHECKED) {
                  
                      ShowWindow(ghSb, SW_HIDE);
                      CheckMenuItem(ghMenu, IDM_VIEW_STB, MF_UNCHECKED);  
                  } else {
                  
                      ShowWindow(ghSb, SW_SHOWNA);
                      CheckMenuItem(ghMenu, IDM_VIEW_STB, MF_CHECKED);  
                  }
                  
                  break;
          }
          
          break;

      case WM_SIZE:
      
          SendMessage(ghSb, WM_SIZE, wParam, lParam);          
          break;

      case WM_DESTROY:
      
          PostQuitMessage(0);
          break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}