void OnScreenDisplayWnd::Display(char * str, int timeout)
{
   SIZE size;
   HFONT defFont;
   HDC hdc;

   if (str != m_text)
      strncpy(m_text, str, sizeof(m_text));

   hdc = GetWindowDC(m_hWnd);
   defFont = (HFONT)SelectObject(hdc, m_font);
   SetTextColor(hdc, m_fgColor);
   GetTextExtentPoint32(hdc, m_text, strlen(m_text), &size);
   SelectObject(hdc, defFont);
   ReleaseDC(m_hWnd, hdc);

   //HACK: to erase the background, hide the window...
   if (!m_hasBackground && IsWindowVisible(m_hWnd))
      ShowWindowAsync(m_hWnd, SW_HIDE);

   SetWindowPos(m_hWnd, NULL, 0, 0, size.cx+10, size.cy+10, 
                SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOREPOSITION);
   InvalidateRect(m_hWnd, NULL, TRUE);

   ShowWindowAsync(m_hWnd, SW_SHOW);
   m_lastTimeout = timeout;
   if (timeout)
      SetTimer(m_hWnd, 1, timeout, NULL);
}