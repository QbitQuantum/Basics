void TSensorView::ColorViewer(TDC& dc,PSHORTREAL pData)
{
  int zMax = m_nDimSize[m_nDim-1],
      xMax = m_nDim > 1 ? m_nDimSize[0] : 1,
      yMax = m_nDim > 2 ? m_nDimSize[1] : 1;
  dc.SetWindowExt(TSize(xMax,yMax));
  for (int y = 0; y < yMax; y++)
  {
    int xStart = 0,
        x = 0;
    TColor clrLast,
           clrThis;
    while(x < xMax)
    {
      int Color[3] = {0,0,0};
      for (int z = 0; z < zMax; z++)
      {
        SHORTREAL r = pData[x + y * (LONGINT) xMax
                              + z * (LONGINT) xMax
                                  * (LONGINT) yMax];
        if (r > 1)
          r = 1;
        else if (r < 0)
          r = 0;
        Color[z] = (int) (pow(r,m_dBright) * 255);
      }
      clrThis = TColor(Color[0],Color[1],Color[2]);
      if(!x)
        clrLast = clrThis;
      else if(clrThis != clrLast)
      {
        TBrush br(clrLast);
        TRect rect(xStart,y,x,y+1);
        dc.FillRect(rect,br);
        xStart = x;
        clrLast = clrThis;
      }
      x++;
    }
    TBrush br(clrLast);
    TRect rect(xStart,y,x,y+1);
    dc.FillRect(rect,br);
  }
  Grid2D(dc);
}