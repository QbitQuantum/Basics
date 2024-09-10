void WMeasurePaintDevice::drawArc(const WRectF& rect, double startAngle,
				  double spanAngle)
{
  WPainterPath p;

  double r = std::max(rect.width(), rect.height()) / 2;
  double cx = rect.center().x();
  double cy = rect.center().y();
  p.arcMoveTo(cx, cy, r, startAngle);
  p.arcTo(cx, cy, r, startAngle, spanAngle);

  expandBounds(p.controlPointRect());
}