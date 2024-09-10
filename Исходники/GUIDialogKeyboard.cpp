bool CGUIDialogKeyboard::OnAction(const CAction &action)
{
  // check if we're doing a search, and if so, interrupt the search timer.
  DWORD now = timeGetTime();
  if (m_lastSearchUpdate || m_lastSearchUpdate + SEARCH_DELAY >= now)
    m_lastSearchUpdate = now;

  if (action.wID == ACTION_BACKSPACE
#ifdef __APPLE__
     || action.wID == ACTION_PARENT_DIR
#endif
     )
  {
    Backspace();
    return true;
  }
  else if (action.wID == ACTION_ENTER)
  {
    OnOK();
    return true;
  }
  else if (action.wID == ACTION_CURSOR_LEFT)
  {
    MoveCursor( -1);
    return true;
  }
  else if (action.wID == ACTION_CURSOR_RIGHT)
  {
    if ((unsigned int) GetCursorPos() == m_strEdit.size() && (m_strEdit.size() == 0 || m_strEdit[m_strEdit.size() - 1] != ' '))
    { // add a space
      Character(L' ');
    }
    else
      MoveCursor(1);
    return true;
  }
  else if (action.wID == ACTION_SHIFT)
  {
    OnShift();
    return true;
  }
  else if (action.wID == ACTION_SYMBOLS)
  {
    OnSymbols();
    return true;
  }
  else if (action.wID >= REMOTE_0 && action.wID <= REMOTE_9)
  {
    OnRemoteNumberClick(action.wID);
    return true;
  }
  else if (action.wID >= (WORD)KEY_VKEY && action.wID < (WORD)KEY_ASCII)
  { // input from the keyboard (vkey, not ascii)
    BYTE b = action.wID & 0xFF;
    if (b == 0x25) MoveCursor( -1);     // left
    else if (b == 0x27) MoveCursor(1);  // right
    else if (b == 0x0D) OnOK();         // enter
    else if (b == 0x08) Backspace();    // backspace
    else if (b == 0x1B) Close();        // escape
    else if (b == 0x20) Character(b);   // space
    return true;
  }
  else if (action.wID >= KEY_ASCII)
  { // input from the keyboard
    //char ch = action.wID & 0xFF;
    switch (action.unicode)
    {
    case 13:  // enter
    case 10:  // enter
      OnOK();
      break;
    case 8:   // backspace
      Backspace();
      break;
    case 27:  // escape
      Close();
      break;
    default:  //use character input
      Character(action.unicode);
      break;
    }
    return true;
  }
  return CGUIDialog::OnAction(action);
}