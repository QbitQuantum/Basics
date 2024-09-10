void
TGaugeGadget::Paint(TDC& dc, bool erase, TRect &rect)
{
  // Select the approprate font
  dc.SelectObject(Window->GetFont());
  TGauge::Paint(dc, erase, rect);
  dc.RestoreFont();
}