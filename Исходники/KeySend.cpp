void CKeySend::SetCapsLock(const bool bState)
{
  BYTE keyState[256];

  GetKeyboardState((LPBYTE)&keyState);
  if ((bState && !(keyState[VK_CAPITAL] & 0x01)) ||
      (!bState && (keyState[VK_CAPITAL] & 0x01))) {
    if (m_impl->m_isOldOS) {
      // Simulate a key press
      keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
      // Simulate a key release
      keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    } else {
      newSendVK(VK_CAPITAL); // Send CapLock keydown/keyup via SendInput
    }
  }

  MSG msg;
  while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
    // so there is a message process it.
#ifndef __WX__
    if (!AfxGetThread()->PumpMessage())
      break;
#else
    // Not sure this is correct!
    if (msg.message == WM_QUIT) {
      // Put it back on the queue and leave now
      ::PostQuitMessage(0);
      return;
    }
      
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
#endif
  }
}