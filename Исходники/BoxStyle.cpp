QPainterPath BoxStyle::getRectanglePath(qreal x, qreal y, int width, int height) const
{
	QPainterPath path;
	int radius = cornerRadius_;
	if (radius > width/2) radius = width/2;
	if (radius > height/2) radius = height/2;

	path.moveTo(width + x, radius + y);

	if ( corner_ == CornerType::RightAngle ) path.lineTo(width + x, y);
	else if ( corner_ == CornerType::Cut ) path.lineTo(width + x - radius, y);
	else path.arcTo(width - 2 * radius + x, y, radius * 2, radius * 2, 0.0, 90.0);

	path.lineTo(radius + x, y);

	if ( corner_ == CornerType::RightAngle ) path.lineTo(x, y);
	else if ( corner_ == CornerType::Cut ) path.lineTo(x, radius + y);
	else path.arcTo(x, y, radius * 2, radius * 2, 90.0, 90.0);

	path.lineTo(x, height - radius + y);

	if ( corner_ == CornerType::RightAngle ) path.lineTo(x, height + y);
	else if ( corner_ == CornerType::Cut ) path.lineTo(x + radius, height + y);
	else path.arcTo(x, height - 2 * radius + y, radius * 2, radius * 2, 180.0, 90.0);

	path.lineTo(width - radius + x, height + y);

	if ( corner_ == CornerType::RightAngle ) path.lineTo(width + x, height + y);
	else if ( corner_ == CornerType::Cut ) path.lineTo(x + width, height - radius + y);
	else path.arcTo(width - 2 * radius + x, height - 2 * radius + y, radius * 2, radius * 2, 270.0, 90.0);

	path.closeSubpath();
	return path;
}