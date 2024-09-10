void
WindArrowRenderer::Draw(Canvas &canvas, const Angle screen_angle,
                        const SpeedVector wind, const PixelPoint pos,
                        const PixelRect rc, WindArrowStyle arrow_style)
{
  // Draw arrow (and tail)

  const unsigned length = uround(Quadruple(wind.norm));
  DrawArrow(canvas, pos, wind.bearing - screen_angle, length, arrow_style);

  // Draw wind speed label

  StaticString<12> buffer;
  buffer.Format(_T("%i"), iround(Units::ToUserWindSpeed(wind.norm)));

  canvas.SetTextColor(COLOR_BLACK);
  canvas.Select(*look.font);

  const unsigned offset = uround(M_SQRT2 * wind.norm);
  BulkPixelPoint label[] = {
    { 18, -26 - int(offset) },
  };
  PolygonRotateShift(label, ARRAY_SIZE(label),
                     pos, wind.bearing - screen_angle);

  TextInBoxMode style;
  style.align = TextInBoxMode::Alignment::CENTER;
  style.vertical_position = TextInBoxMode::VerticalPosition::CENTERED;
  style.shape = LabelShape::OUTLINED;

  TextInBox(canvas, buffer, label[0].x, label[0].y, style, rc);
}