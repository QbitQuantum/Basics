LRESULT HubMessageControl::onPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
  CPaintDC dc(m_hWnd);
  CRect r;
  GetClientRect(r);
  dc.FillRect(r, GetSysColorBrush(COLOR_INFOBK));
  CIcon helpIcon;
  helpIcon.LoadIcon(IDI_SETTINGS_HELP, ICON_WIDTH, ICON_HEIGHT);
  if (helpIcon) {
    helpIcon.DrawIconEx(dc, (m_leftMargin - ICON_WIDTH) / 2, (r.Height() - ICON_HEIGHT) / 2, ICON_WIDTH, ICON_HEIGHT);
  }
  dc.SetBkColor(GetSysColor(COLOR_INFOBK));
  dc.SetTextColor(GetSysColor(COLOR_INFOTEXT));
  const HFONT oldFont = dc.SelectFont(WinUtil::systemFont);
  r.top += m_topMargin;
  r.left += m_leftMargin;
  r.right -= m_rightMargin;
  r.bottom -= m_bottomMargin;
  const int screenTop = r.top;
  const int screenBottom = r.bottom;
  r.top -= scrollTop;
  for (HubMessageIterator i = messages.begin(); i != messages.end(); ++i) {
    const HubMessage& msg = *i;
    r.bottom = r.top + msg.height;
    //dcdebug("scrollTop=%d r.top=%d r.bottom=%d screenTop=%d screenBottom=%d \n", scrollTop, r.top, r.bottom, screenTop, screenBottom);
    if (r.bottom > screenTop) {
      tstring tmp = msg.time + _T(" ") + msg.text;
      dc.DrawText(tmp.c_str(), tmp.length(), r, DT_WORDBREAK);
    }
    if (r.bottom >= screenBottom) break;
    r.top = r.bottom;
  }
  dc.SelectFont(oldFont);
  if (GetFocus() == m_hWnd) {
    drawFocusRect(dc);
  }
  return 0;
}