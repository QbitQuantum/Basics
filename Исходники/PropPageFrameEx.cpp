void CPropPageFrameEx::FillGDIGradientRectH(CDC *pDc, const RECT &rect, COLORREF clrLeft, COLORREF clrRight)
{
  TRIVERTEX        vert[2] ;
  GRADIENT_RECT    gRect;
  vert [0] .x      = rect.left;
  vert [0] .y      = rect.top;
  vert [0] .Red    = (short)(GetRValue( clrLeft ) << 8);
  vert [0] .Green  = (short)(GetGValue( clrLeft ) << 8);
  vert [0] .Blue   = (short)(GetBValue( clrLeft ) << 8);
  vert [0] .Alpha  = 0x0000;

  vert [1] .x      = rect.right;
  vert [1] .y      = rect.bottom; 
  vert [1] .Red    = (short)(GetRValue( clrRight ) << 8);
  vert [1] .Green  = (short)(GetGValue( clrRight ) << 8);
  vert [1] .Blue   = (short)(GetBValue( clrRight ) << 8);
  vert [1] .Alpha  = 0x0000;

  gRect.UpperLeft  = 0;
  gRect.LowerRight = 1;

  GradientFill( pDc->m_hDC,vert,2,&gRect,1, GRADIENT_FILL_RECT_H ); 
}