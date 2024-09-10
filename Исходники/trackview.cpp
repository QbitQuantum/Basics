void TrackView::paintLeftMargin(QStylePainter &painter, const QRegion &region)
{
	const QRect &rect = region.boundingRect();
	const SyncDocument *doc = getDocument();

	int firstRow = qBound(0, getRowFromPhysicalY(qMax(rect.top(), topMarginHeight)), getRows() - 1);
	int lastRow = qBound(0, getRowFromPhysicalY(qMax(rect.bottom(), topMarginHeight)), getRows() - 1);

	painter.setClipRect(QRectF(QPointF(0.0f, topMarginHeight - 0.5f),
	                           QPointF(leftMarginWidth - 0.5f, rect.bottom() + 1.0f)));

	QRectF padding(QPointF(rect.left(), topMarginHeight - 0.5f),
	               QPointF(leftMarginWidth - 0.5f, rect.bottom() + 1.0f));
	painter.fillRect(padding, palette().dark());

	for (int row = firstRow; row <= lastRow; ++row) {
		QRect leftMargin(0, getPhysicalY(row), leftMarginWidth, rowHeight);
		if (!region.intersects(leftMargin))
			continue;

		QBrush fillBrush;
		if (row == editRow)
			fillBrush = editBrush;
		else if (doc->isRowBookmark(row))
			fillBrush = bookmarkBrush;
		else
			fillBrush = palette().button();

		painter.fillRect(leftMargin.adjusted(1, 1, -1, -1), fillBrush);
		qDrawWinButton(&painter, leftMargin, QPalette(fillBrush.color()));

		if ((row % 8) == 0)      painter.setPen(QColor(0, 0, 0));
		else if ((row % 4) == 0) painter.setPen(QColor(64, 64, 64));
		else                     painter.setPen(QColor(128, 128, 128));

		painter.drawText(leftMargin, QString("%1").arg(row, 5, 16, QChar('0')).toUpper() + "h");
	}
}