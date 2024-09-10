void
CrossSectionRenderer::Paint(Canvas &canvas, const PixelRect rc) const
{
  DrawVerticalGradient(canvas, rc,
                       look.sky_color, look.background_color,
                       look.background_color);

  canvas.SetTextColor(look.text_color);
  canvas.Select(*look.grid_font);

  ChartRenderer chart(chart_look, canvas, rc);

  if (!vec.IsValid() || !start.IsValid()) {
    chart.DrawNoData(_("Not moving"));
    return;
  }

  const auto nav_altitude = gps_info.NavAltitudeAvailable()
    ? gps_info.nav_altitude
    : 0.;
  auto hmin = fdim(nav_altitude, 3300);
  auto hmax = std::max(3300., nav_altitude + 1000.);

  chart.ResetScale();
  chart.ScaleXFromValue(0);
  chart.ScaleXFromValue(vec.distance);
  chart.ScaleYFromValue(hmin);
  chart.ScaleYFromValue(hmax);

  TerrainHeight elevations[NUM_SLICES];
  UpdateTerrain(elevations);

  if (airspace_database != nullptr) {
    const AircraftState aircraft = ToAircraftState(Basic(), Calculated());
    airspace_renderer.Draw(canvas, chart, *airspace_database, start, vec,
                           aircraft);
  }

  terrain_renderer.Draw(canvas, chart, elevations);
  PaintGlide(chart);
  PaintAircraft(canvas, chart, rc);
  PaintGrid(canvas, chart);
}