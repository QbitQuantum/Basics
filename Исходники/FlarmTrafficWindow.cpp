/**
 * Paints the traffic symbols on the given canvas
 * @param canvas The canvas to paint on
 */
void
FlarmTrafficWindow::PaintRadarTarget(Canvas &canvas,
                                     const FlarmTraffic &traffic,
                                     unsigned i)
{
  // Save relative East/North
  fixed x = traffic.relative_east;
  fixed y = -traffic.relative_north;

  // Calculate the distance in pixels
  fixed scale = RangeScale(traffic.distance);

  // Don't display distracting, far away targets in WarningMode
  if (WarningMode() && !traffic.HasAlarm() && scale == fixed(radius))
    return;

  // x and y are not between 0 and 1 (distance will be handled via scale)
  if (!traffic.distance.IsZero()) {
    x /= traffic.distance;
    y /= traffic.distance;
  } else {
    x = fixed_zero;
    y = fixed_zero;
  }

  if (!enable_north_up) {
    // Rotate x and y to have a track up display
    FastRotation::Pair p = fr.Rotate(x, y);
    x = fixed(p.first);
    y = fixed(p.second);
  }

  // Calculate screen coordinates
  sc[i].x = radar_mid.x + iround(x * scale);
  sc[i].y = radar_mid.y + iround(y * scale);

  const Color *text_color;
  const Pen *target_pen, *circle_pen;
  const Brush *target_brush, *arrow_brush;
  bool hollow_brush = false;
  unsigned circles = 0;

  // Set the arrow color depending on alarm level
  switch (traffic.alarm_level) {
  case FlarmTraffic::AlarmType::LOW:
    text_color = &look.default_color;
    target_pen = circle_pen = &look.warning_pen;
    target_brush = &look.warning_brush;
    arrow_brush = &look.default_brush;
    circles = 1;
    break;
  case FlarmTraffic::AlarmType::IMPORTANT:
  case FlarmTraffic::AlarmType::URGENT:
    text_color = &look.default_color;
    target_pen = circle_pen = &look.alarm_pen;
    target_brush = &look.alarm_brush;
    arrow_brush = &look.default_brush;
    circles = 2;
    break;
  case FlarmTraffic::AlarmType::NONE:
    if (WarningMode()) {
      text_color = &look.passive_color;
      target_pen = &look.passive_pen;
      arrow_brush = &look.passive_brush;
      hollow_brush = true;
    } else {
      // Search for team color
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
          circle_pen = &look.team_pen_green;
          break;
        case FlarmFriends::BLUE:
          circle_pen = &look.team_pen_blue;
          break;
        case FlarmFriends::YELLOW:
          circle_pen = &look.team_pen_yellow;
          break;
        case FlarmFriends::MAGENTA:
          circle_pen = &look.team_pen_magenta;
          break;
        default:
          break;
        }

        circles = 1;
      }

      if (!small && static_cast<unsigned> (selection) == i) {
        text_color = &look.selection_color;
        target_brush = arrow_brush = &look.selection_brush;
        target_pen = &look.selection_pen;
      } else {
        hollow_brush = true;
        if (traffic.IsPassive()) {
          text_color = &look.passive_color;
          target_pen = &look.passive_pen;
          arrow_brush = &look.passive_brush;
        } else {
          text_color = &look.default_color;
          target_pen = &look.default_pen;
          arrow_brush = &look.default_brush;
        }
      }
    }
    break;
  }

  if (circles > 0) {
    canvas.SelectHollowBrush();
    canvas.Select(*circle_pen);
    canvas.circle(sc[i].x, sc[i].y, Layout::FastScale(small ? 8 : 16));
    if (circles == 2)
      canvas.circle(sc[i].x, sc[i].y, Layout::FastScale(small ? 10 : 19));
  }

  // Create an arrow polygon
  RasterPoint Arrow[5];
  if (small) {
    Arrow[0].x = -3;
    Arrow[0].y = 4;
    Arrow[1].x = 0;
    Arrow[1].y = -5;
    Arrow[2].x = 3;
    Arrow[2].y = 4;
    Arrow[3].x = 0;
    Arrow[3].y = 2;
    Arrow[4].x = -3;
    Arrow[4].y = 4;
  } else {
    Arrow[0].x = -6;
    Arrow[0].y = 8;
    Arrow[1].x = 0;
    Arrow[1].y = -10;
    Arrow[2].x = 6;
    Arrow[2].y = 8;
    Arrow[3].x = 0;
    Arrow[3].y = 5;
    Arrow[4].x = -6;
    Arrow[4].y = 8;
  }

  // Rotate and shift the arrow
  PolygonRotateShift(Arrow, 5, sc[i].x, sc[i].y,
                     traffic.track - (enable_north_up ?
                                             Angle::Zero() : heading));

  // Select pen and brush
  canvas.Select(*target_pen);
  if (hollow_brush)
    canvas.SelectHollowBrush();
  else
    canvas.Select(*target_brush);

  // Draw the polygon
  canvas.polygon(Arrow, 5);

  if (small) {
    if (WarningMode() && !traffic.HasAlarm())
      return;

    const short relalt =
        iround(Units::ToUserAltitude(traffic.relative_altitude) / 100);

    // if (relative altitude is other than zero)
    if (relalt == 0)
      return;

    // Write the relativ altitude devided by 100 to the Buffer
    StaticString<10> buffer;
    buffer.Format(_T("%d"), abs(relalt));

    // Select font
    canvas.SetBackgroundTransparent();
    canvas.Select(look.side_info_font);
    canvas.SetTextColor(*text_color);

    // Calculate size of the output string
    PixelSize tsize = canvas.CalcTextSize(buffer);

    UPixelScalar dist = Layout::FastScale(traffic.HasAlarm() ? 12 : 8);

    // Draw string
    canvas.text(sc[i].x + dist, sc[i].y - tsize.cy / 2, buffer);

    // Set target_brush for the up/down arrow
    canvas.Select(*arrow_brush);
    canvas.SelectNullPen();

    // Prepare the triangular polygon
    RasterPoint triangle[4];
    triangle[0].x = 0;
    triangle[0].y = -4;
    triangle[1].x = 3;
    triangle[1].y = 0;
    triangle[2].x = -3;
    triangle[2].y = 0;

    // Flip = -1 for arrow pointing downwards
    short flip = 1;
    if (relalt < 0)
      flip = -1;

    // Shift the arrow to the right position
    for (int j = 0; j < 3; j++) {
      triangle[j].x = Layout::FastScale(triangle[j].x);
      triangle[j].y = Layout::FastScale(triangle[j].y);

      triangle[j].x = sc[i].x + dist + triangle[j].x + tsize.cx / 2;
      triangle[j].y = sc[i].y + flip * (triangle[j].y  - tsize.cy / 2);
    }
    triangle[3].x = triangle[0].x;
    triangle[3].y = triangle[0].y;

    // Draw the arrow
    canvas.DrawTriangleFan(triangle, 4);

    return;
  }

  // if warning exists -> don't draw vertical speeds
  if (WarningMode())
    return;

  // if vertical speed to small or negative -> skip this one
  if (side_display_type == 1 &&
      (!traffic.climb_rate_avg30s_available ||
       traffic.climb_rate_avg30s < fixed(0.5) ||
       traffic.IsPowered()))
      return;

  // Select font
  canvas.SetBackgroundTransparent();
  canvas.Select(look.side_info_font);

  // Format string
  TCHAR tmp[10];

  if (side_display_type == 1)
    FormatUserVerticalSpeed(traffic.climb_rate_avg30s, tmp, false);
  else
    FormatRelativeUserAltitude(traffic.relative_altitude, tmp, true);

  PixelSize sz = canvas.CalcTextSize(tmp);

  // Draw vertical speed shadow
  canvas.SetTextColor(COLOR_WHITE);
  canvas.text(sc[i].x + Layout::FastScale(11) + 1,
              sc[i].y - sz.cy / 2 + 1, tmp);
  canvas.text(sc[i].x + Layout::FastScale(11) - 1,
              sc[i].y - sz.cy / 2 - 1, tmp);

  // Select color
  canvas.SetTextColor(*text_color);

  // Draw vertical speed
  canvas.text(sc[i].x + Layout::FastScale(11), sc[i].y - sz.cy / 2, tmp);
}