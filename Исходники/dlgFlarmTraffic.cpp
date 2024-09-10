/**
 * Paints the basic info for the selected target on the given canvas
 * @param canvas The canvas to paint on
 */
void
FlarmTrafficControl::PaintTrafficInfo(Canvas &canvas) const
{
  // Don't paint numbers if no plane selected
  if (selection == -1 && !WarningMode())
    return;

  // Shortcut to the selected traffic
  FlarmTraffic traffic = data.traffic[WarningMode() ? warning : selection];
  assert(traffic.IsDefined());

  // Temporary string
  TCHAR tmp[20];
  // Temporary string size
  PixelSize sz;

  PixelRect rc;
  rc.left = padding;
  rc.top = padding;
  rc.right = canvas.get_width() - padding;
  rc.bottom = canvas.get_height() - padding;

  // Set the text color and background
  switch (traffic.alarm_level) {
  case FlarmTraffic::AlarmType::LOW:
    canvas.SetTextColor(look.warning_color);
    break;
  case FlarmTraffic::AlarmType::IMPORTANT:
  case FlarmTraffic::AlarmType::URGENT:
    canvas.SetTextColor(look.alarm_color);
    break;
  case FlarmTraffic::AlarmType::NONE:
    canvas.SetTextColor(look.default_color);
    break;
  }
  canvas.SetBackgroundTransparent();

  // Climb Rate
  if (!WarningMode() && traffic.climb_rate_avg30s_available) {
    Units::FormatUserVerticalSpeed(traffic.climb_rate_avg30s, tmp, 20);
    canvas.Select(look.info_values_font);
    sz = canvas.CalcTextSize(tmp);
    canvas.text(rc.right - sz.cx, rc.top + look.info_labels_font.GetHeight(), tmp);

    canvas.Select(look.info_labels_font);
    sz = canvas.CalcTextSize(_("Vario"));
    canvas.text(rc.right - sz.cx, rc.top, _("Vario"));
  }

  // Distance
  Units::FormatUserDistanceSmart(traffic.distance, tmp, 20);
  canvas.Select(look.info_values_font);
  sz = canvas.CalcTextSize(tmp);
  canvas.text(rc.left, rc.bottom - sz.cy, tmp);

  canvas.Select(look.info_labels_font);
  canvas.text(rc.left,
              rc.bottom - look.info_values_font.GetHeight() - look.info_labels_font.GetHeight(),
              _("Distance"));

  // Relative Height
  Units::FormatRelativeUserAltitude(traffic.relative_altitude, tmp, 20);
  canvas.Select(look.info_values_font);
  sz = canvas.CalcTextSize(tmp);
  canvas.text(rc.right - sz.cx, rc.bottom - sz.cy, tmp);

  canvas.Select(look.info_labels_font);
  sz = canvas.CalcTextSize(_("Rel. Alt."));
  canvas.text(rc.right - sz.cx,
              rc.bottom - look.info_values_font.GetHeight() - look.info_labels_font.GetHeight(),
              _("Rel. Alt."));

  // ID / Name
  unsigned font_size;
  if (traffic.HasName()) {
    canvas.Select(look.call_sign_font);
    font_size = look.call_sign_font.GetHeight();

    if (!traffic.HasAlarm())
      canvas.SetTextColor(look.selection_color);

    _tcscpy(tmp, traffic.name);
  } else {
    font_size = look.info_labels_font.GetHeight();
    traffic.id.Format(tmp);
  }

  if (!WarningMode()) {
    // Team color dot
    FlarmFriends::Color team_color = FlarmFriends::GetFriendColor(traffic.id);

    // If no color found but target is teammate
    if (team_color == FlarmFriends::NONE &&
        settings.team_flarm_tracking &&
        traffic.id == settings.team_flarm_id)
      // .. use yellow color
      team_color = FlarmFriends::GREEN;

    // If team color found -> draw a colored circle around the target
    if (team_color != FlarmFriends::NONE) {
      switch (team_color) {
      case FlarmFriends::GREEN:
        canvas.Select(look.team_brush_green);
        break;
      case FlarmFriends::BLUE:
        canvas.Select(look.team_brush_blue);
        break;
      case FlarmFriends::YELLOW:
        canvas.Select(look.team_brush_yellow);
        break;
      case FlarmFriends::MAGENTA:
        canvas.Select(look.team_brush_magenta);
        break;
      default:
        break;
      }

      canvas.SelectNullPen();
      canvas.circle(rc.left + Layout::FastScale(7), rc.top + (font_size / 2),
                    Layout::FastScale(7));

      rc.left += Layout::FastScale(16);
    }
  }

  canvas.text(rc.left, rc.top, tmp);
}