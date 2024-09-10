static void
Draw(Canvas &canvas, PixelRect rc,
     const ArrivalAltitudeMapItem &item,
     const TwoTextRowsRenderer &row_renderer,
     const FinalGlideBarLook &look)
{
  const unsigned line_height = rc.GetHeight();

  bool reach_relevant = item.reach.IsReachRelevant();

  int arrival_altitude =
    item.reach.terrain_valid == ReachResult::Validity::VALID
    ? item.reach.terrain
    : item.reach.direct;
  if (item.HasElevation())
    arrival_altitude -= item.elevation;

  bool reachable =
    item.reach.terrain_valid != ReachResult::Validity::UNREACHABLE &&
    arrival_altitude >= 0;

  // Draw final glide arrow icon

  const PixelPoint pt(rc.left + line_height / 2, rc.top + line_height / 2);

  BulkPixelPoint arrow[] = {
      { -7, -3 }, { 0, 4 }, { 7, -3 }
  };

  Angle arrow_angle = reachable ? Angle::HalfCircle() : Angle::Zero();
  PolygonRotateShift(arrow, ARRAY_SIZE(arrow), pt, arrow_angle);

  if (reachable) {
    canvas.Select(look.brush_above);
    canvas.Select(look.pen_above);
  } else {
    canvas.Select(look.brush_below);
    canvas.Select(look.pen_below);
  }
  canvas.DrawPolygon(arrow, ARRAY_SIZE(arrow));

  const unsigned text_padding = Layout::GetTextPadding();
  rc.left += line_height + text_padding;

  // Format title row

  TCHAR altitude_buffer[32];
  StaticString<256> buffer;
  buffer.clear();

  if (item.HasElevation()) {
    int relative_arrival_altitude =
      item.reach.direct - item.elevation;

    FormatRelativeUserAltitude(relative_arrival_altitude,
                               altitude_buffer, ARRAY_SIZE(altitude_buffer));

    buffer.AppendFormat(_T("%s %s, "), altitude_buffer, _("AGL"));
  }

  buffer.AppendFormat(_T("%s %s"),
                      FormatUserAltitude(item.reach.direct).c_str(),
                      _("MSL"));

  // Draw title row

  row_renderer.DrawFirstRow(canvas, rc, buffer);

  // Format comment row

  if (reach_relevant) {
    buffer.Format(_T("%s: "), _("around terrain"));

    if (item.HasElevation()) {
      int relative_arrival_altitude =
          item.reach.terrain - item.elevation;

      FormatRelativeUserAltitude(relative_arrival_altitude,
                                 altitude_buffer, ARRAY_SIZE(altitude_buffer));

     buffer.AppendFormat(_T("%s %s, "), altitude_buffer, _("AGL"));
    }

    buffer.AppendFormat(_T("%s %s, "),
                        FormatUserAltitude(item.reach.terrain).c_str(),
                        _("MSL"));
  } else if (item.HasElevation() &&
             item.reach.direct >= item.elevation &&
             item.reach.terrain_valid == ReachResult::Validity::UNREACHABLE) {
    buffer.UnsafeFormat(_T("%s "), _("Unreachable due to terrain."));
  } else {
    buffer.clear();
  }

  buffer += _("Arrival altitude incl. safety height");

  // Draw comment row

  row_renderer.DrawSecondRow(canvas, rc, buffer);
}