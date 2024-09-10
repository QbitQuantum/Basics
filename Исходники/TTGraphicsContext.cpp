void TTGraphicsContext::lineSegment(TTFloat64 x1, TTFloat64 y1, TTFloat64 x2, TTFloat64 y2, TTFloat64 width, TTGraphicsColor& color)
{
	setColor(color);
	setLineWidth(width);
	moveTo(x1, y1);
	lineTo(x2, y2);
	stroke();
}