void
TFlatPainter::Paint(TDC& dc, TRect& rect)
{
  TWindow* wnd = TYPESAFE_DOWNCAST(this, TWindow);
  if(!wnd)
    return;

  if(IsSet(fpMouseIn) && wnd->IsWindowEnabled()){
    // We draw the "tracked" situation
#ifdef TEST
    TBrush brush (TColor::LtRed);
#else
    TBrush brush (TColor::Sys3dFace);
#endif
    dc.FrameRect(rect, brush);
    rect.Inflate(-1, -1);
    dc.FrameRect(rect, brush);
    rect.Inflate(-1, -1);
    dc.FrameRect(rect, brush);
    rect.Inflate(1, 1);
    TUIBorder::DrawEdge(dc, rect, TUIBorder::SunkenOuter, TUIBorder::Rect);
  }
  else{
    // We draw the "untracked" situation
#ifdef TEST
    TBrush brush(TColor::LtBlue);
    TBrush brush2(TColor::LtGreen);
#else
    TBrush brush(TColor::Sys3dFace);
    TBrush brush2(TColor::SysWindow);
#endif

    dc.FrameRect(rect,brush);
    rect.Inflate(-1, -1);
    dc.FrameRect(rect,brush);
    rect.Inflate(-1, -1);
    dc.FrameRect(rect, brush2);
  }
}