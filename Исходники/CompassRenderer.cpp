void
CompassRenderer::Draw(Canvas &canvas, const Angle screen_angle,
                      const RasterPoint pos)
{
  RasterPoint arrow[5] = { { 0, -13 }, { -6, 10 }, { 0, 4 }, { 6, 10 }, { 0, -13 } };

  canvas.select(Graphics::hpCompass);
  canvas.select(Graphics::hbCompass);

  // North arrow
  PolygonRotateShift(arrow, ARRAY_SIZE(arrow), pos.x, pos.y, -screen_angle);
  canvas.polygon(arrow, ARRAY_SIZE(arrow));
}