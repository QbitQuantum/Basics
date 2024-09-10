LRESULT CFindEditCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_SYSCOMMAND && wParam == SC_KEYMENU) {
    // This should be an entry keyboard shortcut!
    CWnd *pWnd = GetFocus();
    if (pWnd == NULL)
      return 0L;

    // But only if we have Focus
    if (pWnd->GetDlgCtrlID() != ID_TOOLBUTTON_FINDEDITCTRL)
      goto exit;

    // Need base character excluding special keys
    short siKeyStateVirtualKeyCode = VkKeyScan(lParam & 0xff);
    WORD wVirtualKeyCode = siKeyStateVirtualKeyCode & 0xff;

    if (wVirtualKeyCode != 0) {
      WORD wModifiers(0);
      if (GetKeyState(VK_CONTROL) & 0x8000)
        wModifiers |= MOD_CONTROL;

      if (GetKeyState(VK_MENU) & 0x8000)
        wModifiers |= MOD_ALT;

      if (GetKeyState(VK_SHIFT) & 0x8000)
        wModifiers |= MOD_SHIFT;

      if (!app.GetMainDlg()->ProcessEntryShortcut(wVirtualKeyCode, wModifiers))
        return 0;
    }
  }

exit:
  return CEditExtn::WindowProc(message, wParam, lParam);
}