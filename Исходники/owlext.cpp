void
FillMaskRect(TDC& dc, TRect rect)
{
  THatch8x8Brush br(THatch8x8Brush::Hatch11F1, TColor::Sys3dHilight,
    TColor::Sys3dFace);
  dc.FillRect(rect, br);
}