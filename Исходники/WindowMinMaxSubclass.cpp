//-----------------------------------------------------------------------------
void CWindowMinMaxSubclass::UnsubclassWindow()
{
#ifdef XP_WIN
  if (m_prevWndProc == NULL) return;
  SetWindowLong(m_hwnd, GWL_WNDPROC, (LONG)m_prevWndProc);
  SetWindowLong(m_hwnd, GWL_USERDATA, 0);
  m_prevWndProc = NULL;

  if(m_hDevNotify != NULL)
  {
    UnregisterDeviceNotification(m_hDevNotify);
    m_hDevNotify = NULL;
  }
#endif
}