void CSeparator::DrawTextImpl(CPaintDC &dc, CString text, CRect clientRect)
{
   auto &g = Globals::Instance();

   HFONT hOldFont = dc.SelectFont(g.sep.font);

   dc.SetTextColor(g.sep.textColor);
   dc.SetBkColor(g.bkColor);

   const int margin = 0;
   CSize textSize;
   dc.GetTextExtent(text, -1, &textSize);
   CRect textRect(clientRect);
   textRect.left = margin;
   textRect.right = textRect.left + textSize.cx + 2 * 3;
   dc.FillSolidRect(textRect, g.bkColor);
   textRect.InflateRect(-3, 0);
   dc.DrawText(text, -1, textRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

   dc.SelectFont(hOldFont);
}