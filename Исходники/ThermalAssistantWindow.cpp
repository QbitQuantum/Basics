void
ThermalAssistantWindow::PaintPoints(Canvas &canvas) const
{
#ifdef ENABLE_OPENGL
  GLBlend blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#elif defined(USE_GDI)
  canvas.SetMixMask();
#endif /* GDI */

  canvas.Select(hbPolygon);
  canvas.Select(hpPolygon);
  canvas.polygon(lift_points, 36);
}