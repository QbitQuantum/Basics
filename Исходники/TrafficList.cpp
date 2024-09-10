void
TrafficListWidget::OnPaintItem(Canvas &canvas, PixelRect rc,
                               unsigned index)
{
  assert(index < items.size());
  Item &item = items[index];

  assert(item.IsFlarm()
#ifdef HAVE_SKYLINES_TRACKING_HANDLER
         || item.IsSkyLines()
#endif
         );

  item.AutoLoad();

  const FlarmNetRecord *record = item.record;
  const TCHAR *callsign = item.callsign;

  const DialogLook &look = UIGlobals::GetDialogLook();
  const Font &name_font = *look.list.font_bold;
  const Font &small_font = look.small_font;

  const unsigned text_padding = Layout::GetTextPadding();
  const unsigned frame_padding = text_padding / 2;

  TCHAR tmp_id[10];
  item.id.Format(tmp_id);

  canvas.Select(name_font);

  StaticString<256> tmp;

  if (item.IsFlarm()) {
    if (record != nullptr)
      tmp.Format(_T("%s - %s - %s"),
                 callsign, record->registration.c_str(), tmp_id);
    else if (callsign != nullptr)
      tmp.Format(_T("%s - %s"), callsign, tmp_id);
    else
      tmp.Format(_T("%s"), tmp_id);
#ifdef HAVE_SKYLINES_TRACKING_HANDLER
  } else if (item.IsSkyLines()) {
    if (!item.name.empty())
      tmp = item.name.c_str();
    else
      tmp.UnsafeFormat(_T("SkyLines %u"), item.skylines_id);
#endif
  } else {
    tmp = _T("?");
  }

  if (item.color != FlarmColor::NONE) {
    const TrafficLook &traffic_look = UIGlobals::GetLook().traffic;

    switch (item.color) {
    case FlarmColor::NONE:
    case FlarmColor::COUNT:
      gcc_unreachable();

    case FlarmColor::GREEN:
      canvas.Select(traffic_look.team_pen_green);
      break;
    case FlarmColor::BLUE:
      canvas.Select(traffic_look.team_pen_blue);
      break;
    case FlarmColor::YELLOW:
      canvas.Select(traffic_look.team_pen_yellow);
      break;
    case FlarmColor::MAGENTA:
      canvas.Select(traffic_look.team_pen_magenta);
      break;
    }

    canvas.SelectHollowBrush();

    const PixelSize size = canvas.CalcTextSize(tmp);
    canvas.Rectangle(rc.left + row_renderer.GetX() - frame_padding,
                     rc.top + row_renderer.GetFirstY() - frame_padding,
                     rc.left + row_renderer.GetX() + size.cx + frame_padding,
                     rc.top + row_renderer.GetFirstY() + size.cy + frame_padding);
  }

  row_renderer.DrawFirstRow(canvas, rc, tmp);

  canvas.Select(small_font);

  /* draw bearing and distance on the right */
  if (item.vector.IsValid()) {
    row_renderer.DrawRightFirstRow(canvas, rc,
                                            FormatUserDistanceSmart(item.vector.distance).c_str());

    // Draw leg bearing
    rc.right = row_renderer.DrawRightSecondRow(canvas, rc,
                                               FormatBearing(item.vector.bearing).c_str());
  }

  if (record != nullptr) {
    tmp.clear();

    if (!record->pilot.empty())
      tmp = record->pilot.c_str();

    if (!record->plane_type.empty()) {
      if (!tmp.empty())
        tmp.append(_T(" - "));

      tmp.append(record->plane_type);
    }

    if (!record->airfield.empty()) {
      if (!tmp.empty())
        tmp.append(_T(" - "));

      tmp.append(record->airfield);
    }

    if (!tmp.empty())
      row_renderer.DrawSecondRow(canvas, rc, tmp);
#ifdef HAVE_SKYLINES_TRACKING_HANDLER
  } else if (item.IsSkyLines()) {
    if (CommonInterface::Basic().time_available) {
      tmp.UnsafeFormat(_("%u minutes ago"),
                       SinceInMinutes(CommonInterface::Basic().time,
                                      item.time_of_day_ms));
    } else
      tmp.clear();

    if (!item.near_name.empty())
      tmp.AppendFormat(_T(" near %s (%s)"),
                       item.near_name.c_str(),
                       FormatUserDistanceSmart(item.near_distance).c_str());

    if (!tmp.empty())
      tmp.append(_T("; "));
    tmp.append(FormatUserAltitude(item.altitude));

    if (!tmp.empty())
      row_renderer.DrawSecondRow(canvas, rc, tmp);
#endif
  }
}