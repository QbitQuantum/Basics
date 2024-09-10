void CPalViewDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
  int x,y;
  CRect Rect;
  CBrush Brush;
  for (x = 0; x < 16; x++)
    for (y = 0; y < 16; y++)
    {
      Rect = CRect (x*12, y*13, x*12+11, y*13+12);
      Rect.OffsetRect (14, 14);
      PLPixel32 Col = m_pPal[x*8+y];
      Brush.CreateSolidBrush (RGB (Col.GetR(), Col.GetG(), Col.GetB ()));
      dc.FillRect (Rect, &Brush);
      Brush.DeleteObject();
    }
}