/**
 * \brief Thread that create window and that monitor event related to it.
 * \param pThreadParam thread parameter
 * \return 0
 */
static unsigned WINAPI CreateWndThreadW(LPVOID pThreadParam)
{
  HINSTANCE hInstance = GetModuleHandle(NULL);
  keyboard_hook* keyboard = (keyboard_hook*)pThreadParam;

  RegisterWindowClassW(hInstance);

  HWND hWnd = CreateWindowW(WINDOW_SHORTCUT_NAME, NULL, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL, hInstance, NULL);
  keyboard->hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyHandler, NULL, 0);

  if(hWnd == NULL)
  {
    fprintf(stderr, "Failed to create window: %d\n", GetLastError());
    fflush(stderr);
    return 0;
  }
  else
  {
    MSG msg;

    keyboard->hwnd = hWnd;
    PostMessage(keyboard->hwnd, WM_HOTKEY, 0, 0);

    while(GetMessageW(&msg, hWnd, 0, 0))
    {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }
    return msg.wParam;
  }
}