void WPainterPath::arcTo(double cx, double cy, double radius,
			 double startAngle, double sweepLength)
{
  arcTo(cx - radius, cy - radius, radius * 2, radius * 2,
	startAngle, sweepLength);
}