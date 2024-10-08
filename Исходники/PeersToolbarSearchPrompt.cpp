LRESULT PeersToolbarSearchPrompt::onPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
  CPaintDC dc(m_hWnd);
  CRect r;
  GetClientRect(r);
  CBrush brush;
  brush.CreateSolidBrush(m_backgroundColor);
  dc.FillRect(r, brush);
  CPen pen;
  pen.CreatePen(PS_SOLID, 1, RGB(132,0,0));
  const HPEN oldPen = dc.SelectPen(pen);
  dc.MoveTo(r.left, r.top + 5);
  dc.LineTo(r.left, r.bottom - 5);
  dc.SelectPen(oldPen);
  const int len = GetWindowTextLength();
  if (len > 0) {
    r.left += m_leftPadding + 1;
    AutoArray<TCHAR> caption(len + 1);
    GetWindowText(caption, len + 1);
    const HFONT oldFont = dc.SelectFont(WinUtil::boldFont);
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(255,255,255));
    dc.DrawText(caption, len, r, DT_SINGLELINE | DT_VCENTER);
    dc.SelectFont(oldFont);
  }
  return 0;
}