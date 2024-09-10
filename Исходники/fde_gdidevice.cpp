FX_BOOL CFDE_GdiDevice::FillChord(IFDE_Brush* pBrush,
                                  const CFX_RectF& rect,
                                  FX_FLOAT startAngle,
                                  FX_FLOAT sweepAngle,
                                  const CFX_Matrix* pMatrix) {
  CFX_ArcF chord;
  chord.Set(rect, startAngle, sweepAngle);
  CFDE_GdiPath path;
  path.AddChord(chord);
  return FillPath(pBrush, &path, pMatrix);
}