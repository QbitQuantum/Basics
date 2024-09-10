QRectF KColorTable::satuationRect()
{
	QRectF drawRt = rect();
	drawRt.setRect(0, height() - HEIGHT_SATUATION, width(), HEIGHT_SATUATION);
	return drawRt;
}