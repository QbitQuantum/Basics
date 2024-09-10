/**
 * Draws the GliderLink traffic icons onto the given canvas
 * @param canvas Canvas for drawing
 */
void
MapWindow::DrawGLinkTraffic(Canvas &canvas,
                            const PixelPoint aircraft_pos) const
{
#ifdef ANDROID

  // Return if FLARM icons on moving map are disabled
  if (!GetMapSettings().show_flarm_on_map)
    return;

  const GliderLinkTrafficList &traffic = Basic().glink_data.traffic;
  if (traffic.IsEmpty())
    return;

  const MoreData &basic = Basic();

  const WindowProjection &projection = render_projection;

  canvas.Select(*traffic_look.font);

  // Circle through the GliderLink targets
  for (const auto &traf : traffic.list) {

    // Save the location of the target
    GeoPoint target_loc = traf.location;

    // Points for the screen coordinates for the icon, name and average climb
    PixelPoint sc, sc_name, sc_av, sc_alt;

    // If FLARM target not on the screen, move to the next one
    if (!projection.GeoToScreenIfVisible(target_loc, sc))
      continue;

    // Draw the callsign above the icon
    sc_name = sc;
    sc_name.x -= Layout::Scale(10);
    sc_name.y -= Layout::Scale(15);

    // Draw the average climb to the right of the icon
    sc_av = sc;
    sc_av.x += Layout::Scale(10);
    sc_av.y -= Layout::Scale(8);

    // Location of altitude label
    sc_alt = sc;
    sc_alt.x -= Layout::Scale(10);
    sc_alt.y -= Layout::Scale(0);

    TextInBoxMode mode;
    mode.shape = LabelShape::OUTLINED;
    mode.align = TextInBoxMode::Alignment::RIGHT;

    // If callsign/name available draw it to the canvas
    if (traf.HasName() && !StringIsEmpty(traf.name))
      TextInBox(canvas, traf.name, sc_name.x, sc_name.y,
                mode, GetClientRect());

    if (traf.climb_rate_received) {

      // If average climb data available draw it to the canvas
      TCHAR label_avg[100];
      FormatUserVerticalSpeed(traf.climb_rate,
                                     label_avg, false);
      mode.align = TextInBoxMode::Alignment::LEFT;
      TextInBox(canvas, label_avg, sc_av.x, sc_av.y, mode, GetClientRect());
    }

    // use GPS altitude to be consistent with GliderLink
    if(basic.gps_altitude_available && traf.altitude_received
        && fabs(double(traf.altitude) - basic.gps_altitude) >= 100.0) {
      // If average climb data available draw it to the canvas
      TCHAR label_alt[100];
      double alt = (double(traf.altitude) - basic.gps_altitude) / 100.0;
      FormatRelativeUserAltitude(alt, label_alt, false);

      mode.align = TextInBoxMode::Alignment::RIGHT;
      TextInBox(canvas, label_alt, sc_alt.x, sc_alt.y, mode, GetClientRect());
    }

    TrafficRenderer::Draw(canvas, traffic_look, traf,
                          traf.track - projection.GetScreenAngle(), sc);
  }
#endif
}