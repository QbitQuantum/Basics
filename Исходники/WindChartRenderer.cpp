void
RenderWindChart(Canvas &canvas, const PixelRect rc,
                const ChartLook &chart_look,
                const FlightStatistics &fs,
                const NMEAInfo &nmea_info,
                const WindStore &wind_store)
{
  unsigned numsteps = 10;
  bool found = true;

  LeastSquares windstats_mag;
  ChartRenderer chart(chart_look, canvas, rc);

  if (fs.altitude_ceiling.y_max - fs.altitude_ceiling.y_min <= fixed(10)) {
    chart.DrawNoData();
    return;
  }

  for (unsigned i = 0; i < numsteps; i++) {
    fixed h = fixed(fs.altitude_ceiling.y_max - fs.altitude_base.y_min) * i /
              (numsteps - 1) + fixed(fs.altitude_base.y_min);

    Vector wind = wind_store.GetWind(nmea_info.time, h, found);
    fixed mag = wind.Magnitude();

    windstats_mag.LeastSquaresUpdate(mag, h);
  }

  chart.ScaleXFromData(windstats_mag);
  chart.ScaleXFromValue(fixed(0));
  chart.ScaleXFromValue(fixed(10));

  chart.ScaleYFromData(windstats_mag);

  chart.DrawXGrid(Units::ToSysSpeed(fixed(5)),
                  ChartLook::STYLE_THINDASHPAPER, fixed(5), true);
  chart.DrawYGrid(Units::ToSysAltitude(fixed(1000)),
                  ChartLook::STYLE_THINDASHPAPER, fixed(1000), true);
  chart.DrawLineGraph(windstats_mag, ChartLook::STYLE_MEDIUMBLACK);

#define WINDVECTORMAG 25

  numsteps = (int)((rc.bottom - rc.top) / WINDVECTORMAG) - 1;

  canvas.Select(chart_look.GetPen(ChartLook::STYLE_MEDIUMBLACK));

  // draw direction vectors
  fixed hfact;
  for (unsigned i = 0; i < numsteps; i++) {
    hfact = fixed(i + 1) / (numsteps + 1);
    fixed h = fixed(fs.altitude_ceiling.y_max - fs.altitude_base.y_min) * hfact +
              fixed(fs.altitude_base.y_min);

    Vector wind = wind_store.GetWind(nmea_info.time, h, found);
    if (windstats_mag.x_max == fixed(0))
      windstats_mag.x_max = fixed(1); // prevent /0 problems
    wind.x /= fixed(windstats_mag.x_max);
    wind.y /= fixed(windstats_mag.x_max);
    fixed mag = wind.Magnitude();
    if (negative(mag))
      continue;

    Angle angle = Angle::FromXY(wind.y, -wind.x);

    RasterPoint point = chart.ToScreen((chart.GetXMin() + chart.GetXMax()) / 2, h);

    DrawArrow(canvas, point, mag * WINDVECTORMAG, angle);
  }

  chart.DrawXLabel(_T("w"), Units::GetSpeedName());
  chart.DrawYLabel(_T("h"), Units::GetAltitudeName());
}