void
GlueMapWindow::DrawPanInfo(Canvas &canvas) const
{
  if (!render_projection.IsValid())
    return;

  GeoPoint location = render_projection.GetGeoLocation();

  TextInBoxMode mode;
  mode.shape = LabelShape::OUTLINED;
  mode.align = TextInBoxMode::Alignment::RIGHT;

  const Font &font = *look.overlay_font;
  canvas.Select(font);

  UPixelScalar padding = Layout::FastScale(4);
  UPixelScalar height = font.GetHeight();
  PixelScalar y = 0 + padding;
  PixelScalar x = render_projection.GetScreenWidth() - padding;

  if (compass_visible)
    /* don't obscure the north arrow */
    /* TODO: obtain offset from CompassRenderer */
    y += Layout::Scale(19) + Layout::FastScale(13);

  if (terrain) {
    short elevation = terrain->GetTerrainHeight(location);
    if (!RasterBuffer::IsSpecial(elevation)) {
      StaticString<64> elevation_short, elevation_long;
      FormatUserAltitude(fixed(elevation),
                                elevation_short.buffer(), elevation_short.MAX_SIZE);

      elevation_long = _("Elevation: ");
      elevation_long += elevation_short;

      TextInBox(canvas, elevation_long, x, y, mode,
                render_projection.GetScreenWidth(),
                render_projection.GetScreenHeight());

      y += height;
    }
  }

  TCHAR buffer[256];
  FormatGeoPoint(location, buffer, ARRAY_SIZE(buffer), _T('\n'));

  TCHAR *start = buffer;
  while (true) {
    TCHAR *newline = _tcschr(start, _T('\n'));
    if (newline != nullptr)
      *newline = _T('\0');

    TextInBox(canvas, start, x, y, mode,
              render_projection.GetScreenWidth(),
              render_projection.GetScreenHeight());

    y += height;

    if (newline == nullptr)
      break;

    start = newline + 1;
  }
}