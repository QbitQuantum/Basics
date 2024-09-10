LPARAM dxfwFireKeyboardEvent(HWND hWnd, LPARAM lparam) {
  DXFW_UNUSED(hWnd);

  RAWINPUT ri;
  UINT size = sizeof(RAWINPUT);
  GetRawInputData((HRAWINPUT)lparam, RID_INPUT, &ri, &size, sizeof(RAWINPUTHEADER));
  if (ri.header.dwType == RIM_TYPEKEYBOARD) {
    dxfwVirtualKeyCode key_code = dxfwGetKeyCode(ri.data.keyboard.VKey);

    dxfwVirtualKeyState state;
    if ((ri.data.keyboard.Flags & RI_KEY_BREAK) != 0) {
      // Key is UP
      dxfwRegisterKeyUp(key_code);
      state = DXFW_KEY_STATE_UP;
    }
    else {
      // Key is DOWN
      dxfwRegisterKeyDown(key_code);
      state = DXFW_KEY_STATE_DOWN;
    }

    dxfwVirtualKeyModifiers modifier_flags = dxfwGetModifierFlags();
    dxfwVirtualKeyState previous_state = dxfwGetPreviousKeyState(key_code);

    HWND active_hwnd = GetActiveWindow();
    struct dxfwWindow* window = dxfwFindWindow(active_hwnd);
    if (window != NULL && window->m_on_keyboard_) {
      (*window->m_on_keyboard_)(window, key_code, modifier_flags, state, previous_state);
    }

    return 0;  // Return 0 to mark the event as handled
  }
  return 1;  // Return 1 to mark the event as NOT handled
}