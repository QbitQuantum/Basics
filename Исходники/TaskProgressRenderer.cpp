void 
TaskProgressRenderer::DrawTaskProgress(const TaskSummary& summary,
                                       Canvas &canvas, 
                                       const PixelRect &rc)
{
  const int radius = std::min(rc.right-rc.left, rc.bottom-rc.top)/2-IBLSCALE(3);
  RasterPoint center;
  center.x = (rc.left+rc.right)/2;
  center.y = (rc.bottom+rc.top)/2;

  const fixed sweep = fixed_two_pi*fixed(0.9);
  Pen pen_f(1, Appearance.InverseInfoBox ? COLOR_WHITE : COLOR_BLACK);

  if (summary.p_remaining<fixed(0.99)) {
    canvas.select(Graphics::hbWind);
    canvas.null_pen();
    canvas.segment(center.x, center.y, radius, Angle::radians(fixed_zero),
                   Angle::radians(sweep*(fixed_one-summary.p_remaining)));
  }

  canvas.select(pen_f);
  canvas.hollow_brush();
  canvas.circle(center.x, center.y, radius);

  unsigned i=0;
  canvas.select(pen_f);
  for (TaskSummary::TaskSummaryPointVector::const_iterator it= summary.pts.begin();
       it != summary.pts.end(); ++it, ++i) {
    Angle a= Angle::radians(it->p*sweep);
    int x = center.x+(int)(radius*a.fastsine());
    int y = center.y-(int)(radius*a.fastcosine());
    int w;
    if (i== summary.active) {
      if (it->achieved) {
        canvas.select(Graphics::hbGreen);
      } else {
        canvas.select(Graphics::hbOrange);
      }
      w = IBLSCALE(3);
    } else if (i< summary.active) {
      if (it->achieved) {
        canvas.select(Graphics::hbGreen);
      } else {
        canvas.select(Graphics::hbNotReachableTerrain);
      }
      w = IBLSCALE(2);
    } else {
      if (it->achieved) {
        canvas.select(Graphics::hbGreen);
      } else {
        canvas.select(Graphics::hbLightGray);
      }
      w = IBLSCALE(1);
    }
    canvas.rectangle(x-w, y-w, x+w, y+w);
  }
}