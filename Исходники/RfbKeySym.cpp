void RfbKeySym::processKeyEvent(unsigned short virtKey,
                                unsigned int addKeyData)
{
  Log::debug(_T("processKeyEvent() function called: virtKey = %#4.4x, addKeyData")
             _T(" = %#x"), (unsigned int)virtKey, addKeyData);
  if (virtKey == VK_LWIN || virtKey == VK_RWIN) { 
    Log::debug(_T("Ignoring the Win key event"));
    return;
  }

  bool down = (addKeyData & 0x80000000) == 0;
  Log::debug(_T("down = %u"), (unsigned int)down);

  bool ctrlPressed = isPressed(VK_CONTROL) || isPressed(VK_RCONTROL);
  bool altPressed = isPressed(VK_MENU) || isPressed(VK_RMENU);
  bool shiftPressed = isPressed(VK_SHIFT) || isPressed(VK_RSHIFT);
  bool capsToggled = (GetKeyState(VK_CAPITAL) & 1) != 0;
  Log::debug(_T("ctrl = %u, alt = %u, shift = %u, caps toggled = %u"),
             (unsigned int)ctrlPressed,
             (unsigned int)altPressed,
             (unsigned int)shiftPressed,
             (unsigned int)capsToggled);

  m_viewerKeyState[virtKey & 255] = down ? 128 : 0;
  m_viewerKeyState[VK_CAPITAL & 255] = capsToggled ? 1 : 0;

  bool extended = (addKeyData & 0x1000000) != 0; 
  Log::debug(_T("extended = %u"), (unsigned int)extended);
  if (extended) {
    switch (virtKey) {
    case VK_CONTROL:
      virtKey = VK_RCONTROL;
      break;
    case VK_MENU:
      virtKey = VK_RMENU;
      break;
    }
  }

  m_serverKeyState[virtKey & 255] = down ? 128 : 0;

  UINT32 rfbSym;
  if (m_keyMap.virtualCodeToKeySym(&rfbSym, virtKey & 255)) {
    Log::debug(_T("The key has been mapped to the %#4.4x rfb symbol"),
               rfbSym);
    sendKeySymEvent(rfbSym, down);
  } else {
    WCHAR outBuff[20];
    HKL currentLayout = GetKeyboardLayout(0);

    int count = ToUnicodeEx(virtKey, 0, m_viewerKeyState, outBuff,
                            sizeof(outBuff) / sizeof(WCHAR),
                            0, currentLayout);
    if (count > 0) {
      count = ToUnicodeEx(virtKey, 0, m_viewerKeyState, outBuff,
                          sizeof(outBuff) / sizeof(WCHAR),
                          0, currentLayout);
    }

    Log::debug(_T("ToUnicodeEx() return %d"), count);

    if (count == 1 && !m_allowProcessCharEvent || count > 1) {
      bool ctrlAltPressed = ctrlPressed && altPressed;
      bool onlyCtrlPressed = ctrlPressed && !altPressed;
      if (ctrlAltPressed) {
        Log::debug(_T("Release the ctrl and alt")
                   _T(" modifiers before send the key event(s)"));
        releaseModifiers();
      }
      for (int i = 0; i < count; i++) {
        if (onlyCtrlPressed && outBuff[i] < 32) {
          if (onlyCtrlPressed && outBuff[i] >= 1 && outBuff[i] <= 26 &&
              !shiftPressed) {
            Log::debug(_T("The %u char is a control symbol then")
                       _T(" it will be increased by 96 to %u"),
                       (unsigned int)outBuff[i], (unsigned int)outBuff[i] + 96);
            outBuff[i] += 96;
          } else {
            Log::debug(_T("The %u char is a control symbol then")
                       _T(" it will be increased by 64 to %u"),
                       (unsigned int)outBuff[i], (unsigned int)outBuff[i] + 64);
            outBuff[i] += 64;
          }
        }
        if (m_keyMap.unicodeCharToKeySym(outBuff[i], &rfbSym)) {
          Log::debug(_T("Sending the %#4.4x rfb symbol"), rfbSym);
          sendKeySymEvent(rfbSym, down);
        } else {
          Log::error(_T("Can't translate the %#4.4x unicode character to an")
                     _T(" rfb symbol to send it"), (unsigned int)outBuff[i]);
        }
      }
      if (ctrlAltPressed) {
        Log::debug(_T("Restore the ctrl and alt")
                   _T(" modifiers after send the key event(s)"));
        restoreModifiers();
      }
    } else if (count == 0) {
      Log::debug(_T("Was get a not printable symbol then try get a printable")
                 _T(" with turned off the ctrl and alt modifiers"));
      unsigned char withoutCtrlAltKbdState[256];
      memcpy(withoutCtrlAltKbdState, m_serverKeyState, sizeof(withoutCtrlAltKbdState));
      withoutCtrlAltKbdState[VK_LCONTROL] = 0;
      withoutCtrlAltKbdState[VK_RCONTROL] = 0;
      withoutCtrlAltKbdState[VK_CONTROL] = 0;
      withoutCtrlAltKbdState[VK_LMENU] = 0;
      withoutCtrlAltKbdState[VK_RMENU] = 0;
      withoutCtrlAltKbdState[VK_MENU] = 0;
      count = ToUnicodeEx(virtKey, 0, withoutCtrlAltKbdState, outBuff,
                          sizeof(outBuff) / sizeof(WCHAR),
                          0, currentLayout);
      Log::debug(_T("ToUnicodeEx() without ctrl and alt return %d"), count);
      if (count == 1) { 
        if (m_keyMap.unicodeCharToKeySym(outBuff[0], &rfbSym)) {
          sendKeySymEvent(rfbSym, down);
        } else {
          Log::error(_T("Can't translate the %#4.4x unicode character to an")
                     _T(" rfb symbol to send it"), (unsigned int)outBuff[0]);
        }
      }
    } else if (count == -1 && down) {
      Log::debug(_T("Dead key pressed, wait for a char event"));
      m_allowProcessCharEvent = true;
    }
  }
}