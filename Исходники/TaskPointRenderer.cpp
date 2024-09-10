void
TaskPointRenderer::DrawIsoline(const AATPoint &tp)
{
  if (!tp.valid() || !IsTargetVisible(tp))
    return;

  AATIsolineSegment seg(tp, task_projection);
  if (!seg.IsValid())
    return;

  #define fixed_twentieth fixed(1.0 / 20.0)

  GeoPoint start = seg.Parametric(fixed_zero);
  GeoPoint end = seg.Parametric(fixed_one);

  if (m_proj.GeoToScreenDistance(start.Distance(end)) <= 2)
    return;

  RasterPoint screen[21];
  screen[0] = m_proj.GeoToScreen(start);
  screen[20] = m_proj.GeoToScreen(end);

  for (unsigned i = 1; i < 20; ++i) {
    fixed t = i * fixed_twentieth;
    GeoPoint ga = seg.Parametric(t);
    screen[i] = m_proj.GeoToScreen(ga);
  }

  canvas.Select(task_look.isoline_pen);
  canvas.SetBackgroundTransparent();
  canvas.DrawPolyline(screen, 21);
  canvas.SetBackgroundOpaque();
}