inline void
AirspaceIntersectionVisitorSlice::Render(const AbstractAirspace &as) const
{
  AirspaceClass type = as.GetType();

  // No intersections for this airspace
  if (intersections.empty())
    return;

  PixelRect rcd;
  // Calculate top and bottom coordinate
  rcd.top = chart.ScreenY(as.GetTopAltitude(state));
  if (as.IsBaseTerrain())
    rcd.bottom = chart.ScreenY(fixed(0));
  else
    rcd.bottom = chart.ScreenY(as.GetBaseAltitude(state));

  int min_x = 1024, max_x = 0;

  // Iterate through the intersections
  for (const auto &i : intersections) {
    const GeoPoint &p_start = i.first;
    const GeoPoint &p_end = i.second;

    rcd.left = chart.ScreenX(start.Distance(p_start));

    // only one edge found, next edge must be beyond screen
    if (p_start == p_end)
      rcd.right = chart.ScreenX(chart.GetXMax());
    else
      rcd.right = chart.ScreenX(start.Distance(p_end));

    if (rcd.left < min_x)
      min_x = rcd.left;

    if (rcd.right > max_x)
      max_x = rcd.right;

    // Draw the airspace
    RenderBox(rcd, type);
  }

  min_x += Layout::GetTextPadding();
  max_x -= Layout::GetTextPadding();

  /* draw the airspace name */
  const TCHAR *name = as.GetName();
  if (name != nullptr && !StringIsEmpty(name) && min_x < max_x) {
    canvas.SetBackgroundTransparent();
    canvas.SetTextColor(COLOR_BLACK);

    const unsigned max_width = max_x - min_x;

    const PixelSize name_size = canvas.CalcTextSize(name);
    const int x = unsigned(name_size.cx) >= max_width
      ? min_x
      : (min_x + max_x - name_size.cx) / 2;
    const int y = (rcd.top + rcd.bottom - name_size.cy) / 2;

    canvas.DrawClippedText(x, y, max_x - x, name);
  }
}