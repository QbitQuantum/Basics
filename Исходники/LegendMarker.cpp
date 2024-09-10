void LegendMarker::draw(QPainter *p, const QwtScaleMap &xMap, const QwtScaleMap &yMap, const QRect &) const
{
	const int x = xMap.transform(xValue());
	const int y = yMap.transform(yValue());

	const int symbolLineLength = symbolsMaxLineLength();

	int width, height;
	QwtArray<long> heights = itemsHeight(y, symbolLineLength, width, height);

	QRect rs = QRect(QPoint(x, y), QSize(width, height));

	drawFrame(p, d_frame, rs);
	drawSymbols(p, rs, heights, symbolLineLength);
	drawLegends(p, rs, heights, symbolLineLength);
}