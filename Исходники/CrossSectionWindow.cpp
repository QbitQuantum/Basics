  /**
   * Renders the AbstractAirspace on the canvas
   * @param as AbstractAirspace to render
   */
  void
  Render(const AbstractAirspace& as)
  {
    int type = as.get_type();
    if (type <= 0)
      return;

    // No intersections for this airspace
    if (m_intersections.empty())
      return;

    // Select pens and brushes
#ifdef ENABLE_SDL
    Color color =
      Graphics::GetAirspaceColour(settings.colours[type]);
#ifdef ENABLE_OPENGL
    color = color.with_alpha(48);
#endif
    Brush brush(color);
#else
    const Brush &brush = Graphics::GetAirspaceBrushByClass(type, settings);
    canvas.set_text_color(light_color(Graphics::GetAirspaceColourByClass(type, settings)));
#endif

    PixelRect rcd;
    // Calculate top and bottom coordinate
    rcd.top = chart.screenY(as.get_top_altitude(state));
    if (as.is_base_terrain())
      rcd.bottom = chart.screenY(fixed_zero);
    else
      rcd.bottom = chart.screenY(as.get_base_altitude(state));

    // Iterate through the intersections
    for (AirspaceIntersectionVector::const_iterator it = m_intersections.begin();
         it != m_intersections.end(); ++it) {
      const GeoPoint p_start = it->first;
      const GeoPoint p_end = it->second;
      const fixed distance_start = start.distance(p_start);
      const fixed distance_end = start.distance(p_end);

      // Determine left and right coordinate
      rcd.left = chart.screenX(distance_start);
      rcd.right = chart.screenX(distance_end);

      // only one edge found, next edge must be beyond screen
      if ((rcd.left == rcd.right) && (p_start == p_end)) {
        rcd.right = chart.screenX(chart.getXmax());
      }

      // Draw the airspace
      RenderBox(rcd, brush, settings.black_outline, type);
    }
  }