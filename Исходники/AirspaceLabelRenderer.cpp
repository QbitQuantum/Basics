void
AirspaceLabelRenderer::DrawInternal(Canvas &canvas,
#ifndef ENABLE_OPENGL
                                    Canvas &stencil_canvas,
#endif
                                    const WindowProjection &projection,
                                    const AirspaceRendererSettings &settings,
                                    const AirspaceWarningCopy &awc,
                                    const AirspacePredicate &visible,
                                    const AirspaceWarningConfig &config)
{
  AirspaceLabelList labels;
  for (const auto &i : airspaces->QueryWithinRange(projection.GetGeoScreenCenter(),
                                                   projection.GetScreenDistanceMeters())) {
    const AbstractAirspace &airspace = i.GetAirspace();
    if (visible(airspace))
      labels.Add(airspace.GetCenter(), airspace.GetType(), airspace.GetBase(),
                 airspace.GetTop());
  }

  if(settings.label_selection == AirspaceRendererSettings::LabelSelection::ALL)
  {
    labels.Sort(config);

    // default paint settings
    canvas.SetTextColor(look.label_text_color);
    canvas.Select(*look.name_font);
    canvas.Select(look.label_pen);
    canvas.Select(look.label_brush);
    canvas.SetBackgroundTransparent();

    // draw
    TCHAR topText[NAME_SIZE + 1];
    TCHAR baseText[NAME_SIZE + 1];

    for (const auto &label : labels) {
      // size of text
      AirspaceFormatter::FormatAltitudeShort(topText, label.top, false);
      PixelSize topSize = canvas.CalcTextSize(topText);
      AirspaceFormatter::FormatAltitudeShort(baseText, label.base, false);
      PixelSize baseSize = canvas.CalcTextSize(baseText);
      int labelWidth = std::max(topSize.cx, baseSize.cx) +
                       2 * Layout::GetTextPadding();
      int labelHeight = topSize.cy + baseSize.cy;

      // box
      const auto pos = projection.GeoToScreen(label.pos);
      PixelRect rect;
      rect.left = pos.x - labelWidth / 2;
      rect.top = pos.y;
      rect.right = rect.left + labelWidth;
      rect.bottom = rect.top + labelHeight;
      canvas.Rectangle(rect.left, rect.top, rect.right, rect.bottom);

#ifdef USE_GDI
      canvas.DrawLine(rect.left + Layout::GetTextPadding(),
                      rect.top + labelHeight / 2,
                      rect.right - Layout::GetTextPadding(),
                      rect.top + labelHeight / 2);
#else
      canvas.DrawHLine(rect.left + Layout::GetTextPadding(),
                       rect.right - Layout::GetTextPadding(),
                       rect.top + labelHeight / 2, look.label_pen.GetColor());
#endif

      // top text
      int x = rect.right - Layout::GetTextPadding() - topSize.cx;
      int y = rect.top;
      canvas.DrawText(x, y, topText);

      // base text
      x = rect.right - Layout::GetTextPadding() - baseSize.cx;
      y = rect.bottom - baseSize.cy;
      canvas.DrawText(x, y, baseText);
    }
  }
}