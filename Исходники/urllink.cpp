//
/// Override TWindow virtual member function to paint the control.
//
void
TUrlLink::Paint(TDC& dc, bool /*erase*/, TRect& /*rect*/)
{
  TPointer<TFont>  tmpFnt; // Object wrapping font handle
  TAPointer<tchar> text;   // Pointer to caption dynamic buffer
  // Select the font
  if(!LinkFont){
    HFONT hFont = HFONT(::SendMessage(::GetParent(*this), WM_GETFONT, 0, 0));
    if (!hFont)
      hFont = HFONT(GetStockObject(ANSI_VAR_FONT));
    if (hFont)
      tmpFnt = new TFont(hFont);
  }
  if (LinkFont) {
    CHECK(LinkFont->IsGDIObject());
    dc.SelectObject(*LinkFont);
  }
  else if (tmpFnt) {
    CHECK(((TFont&)tmpFnt).IsGDIObject());
    dc.SelectObject((TFont&)tmpFnt);
  }
  int len = GetWindowTextLength();
  text = new tchar[len+1];
  GetWindowText(text, len+1);
  TRect textRect;
  GetClientRect(textRect);

  TColor textColor = LinkColor;
  if (bOverControl)
    textColor = HoverColor;
  else if (bVisited)
    textColor = VisitedColor;

  TColor oldColor = dc.SetTextColor(textColor);
  int oldMode = dc.SetBkMode(TRANSPARENT);
  dc.DrawText(&text[0], len, textRect, 0);
  dc.SetBkMode(oldMode);
  dc.SetTextColor(oldColor);

  // Restore font
  if (LinkFont || tmpFnt)
    dc.RestoreFont();
}