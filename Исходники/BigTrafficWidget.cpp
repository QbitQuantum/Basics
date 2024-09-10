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
  FlarmTraffic traffic = data.list[WarningMode() ? warning : selection];
  assert(traffic.IsDefined());

  const unsigned padding = Layout::GetTextPadding();
  PixelRect rc;
  rc.left = padding;
  rc.top = padding;
  rc.right = canvas.GetWidth() - padding;
  rc.bottom = canvas.GetHeight() - padding;

  // Set the text color and background
  switch (traffic.alarm_level) {
  case FlarmTraffic::AlarmType::LOW:
  case FlarmTraffic::AlarmType::INFO_ALERT:
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
  if (!WarningMode() && traffic.climb_rate_avg30s_available)
    PaintClimbRate(canvas, rc, traffic.climb_rate_avg30s);

  // Distance
  PaintDistance(canvas, rc, traffic.distance);

  // Relative Height
  PaintRelativeAltitude(canvas, rc, traffic.relative_altitude);

  // ID / Name
  if (!traffic.HasAlarm())
    canvas.SetTextColor(look.selection_color);

  PaintID(canvas, rc, traffic);
}