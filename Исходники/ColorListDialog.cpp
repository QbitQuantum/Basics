static void
OnPaintListItem(Canvas &canvas, const PixelRect rc, unsigned i)
{
  assert(i < ARRAY_SIZE(AirspaceLook::preset_colors));

  const Color color(AirspaceLook::preset_colors[i]);

  PixelRect rc2 = rc;
  rc2.Grow(-Layout::FastScale(2));

#ifdef USE_GDI
  canvas.DrawFilledRectangle(rc2, color);
  canvas.SelectHollowBrush();
#else
  Brush brush(color);
  canvas.Select(brush);
#endif

  canvas.SelectBlackPen();
  canvas.Rectangle(rc2.left, rc2.top, rc2.right, rc2.bottom);
}