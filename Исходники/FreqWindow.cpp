void FreqWindow::DrawBackground(wxMemoryDC & dc)
{
   Layout();

   mBitmap.reset();

   mPlotRect = mFreqPlot->GetClientRect();

   mBitmap = std::make_unique<wxBitmap>(mPlotRect.width, mPlotRect.height);

   dc.SelectObject(*mBitmap);

   dc.SetBackground(wxBrush(wxColour(254, 254, 254)));// DONT-THEME Mask colour.
   dc.Clear();

   dc.SetPen(*wxBLACK_PEN);
   dc.SetBrush(*wxWHITE_BRUSH);
   dc.DrawRectangle(mPlotRect);

   dc.SetFont(mFreqFont);
}