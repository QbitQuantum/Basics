//
/// Adjusts the message bar and paints a highlight line. Then, PaintGadgets either
/// paints the hint text if any is set or calls TGadgetWindow::PaintGadgets to
/// repaint each gadget.
//
void
TMessageBar::PaintGadgets(TDC& dc, bool erase, TRect& rect)
{
  if (HighlightLine && rect.top == 0)
    dc.TextRect(0, 0, rect.right, TUIMetric::CyBorder, TColor::Sys3dHilight);

  if (!HintText.empty())
  {
    TRect clientRect = GetClientRect();
    int y = (clientRect.bottom - GetFontHeight()) / 2;
    if (HighlightLine)
      clientRect.top += TUIMetric::CyBorder;
    dc.SelectObject(GetFont());
    dc.SetBkColor(TColor::Sys3dFace);
    dc.ExtTextOut(5, y, ETO_OPAQUE, &clientRect, HintText, static_cast<int>(HintText.length()));
  }
  else
  {
    TGadgetWindow::PaintGadgets(dc, erase, rect);
  }
}