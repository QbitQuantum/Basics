// ============================================================================
TOOLINFO* AngleControl::GetToolInfo()
{
   static TOOLINFO ti;
   static TSTR str;

   str.printf(_T("%f%s"), m_degrees, MaxSDK::GetResourceStringAsMSTR(IDS_DEGREE_SYMBOL));

   memset(&ti, 0, sizeof(TOOLINFO));
   ti.cbSize = sizeof(TOOLINFO);
   ti.hwnd = m_hWnd;
   ti.uId = TOOLTIP_ID;
   ti.lpszText = const_cast<TCHAR*>(str.data());
   GetClientRect(m_hWnd, &ti.rect);

   return &ti;
}