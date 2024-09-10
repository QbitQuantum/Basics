void
SymbolRenderer::DrawSign(Canvas &canvas, PixelRect rc, bool plus)
{
  PixelScalar size = std::min(rc.right - rc.left, rc.bottom - rc.top) / 5;
  RasterPoint center = rc.GetCenter();

  // Draw horizontal bar
  canvas.Rectangle(center.x - size, center.y - size / 3,
                   center.x + size, center.y + size / 3);

  if (plus)
    // Draw vertical bar
    canvas.Rectangle(center.x - size / 3, center.y - size,
                     center.x + size / 3, center.y + size);
}