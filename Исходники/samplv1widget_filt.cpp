// Draw curve.
void samplv1widget_filt::paintEvent ( QPaintEvent *pPaintEvent )
{
	QPainter painter(this);

	const QRect& rect = QWidget::rect();
	const int h  = rect.height();
	const int w  = rect.width();

	const int h2 = h >> 1;
	const int h4 = h >> 2;
	const int w4 = w >> 2;
	const int w8 = w >> 3;

	const int iSlope = int(m_fSlope);
	const int ws = w8 - (iSlope == 1 ? (w8 >> 1) : 0);

	int x = w8 + int(m_fCutoff * float(w - w4));
	int y = h2 - int(m_fReso   * float(h + h4));

	QPolygon poly(6);
	QPainterPath path;

	const int iType = (iSlope == 3 ? 4 : int(m_fType));
	// Low, Notch
	if (iType == 0 || iType == 3) {
		if (iType == 3) x -= w8;
		poly.putPoints(0, 6,
			0, h2,
			x - w8, h2,
			x, h2,
			x, y,
			x + ws, h,
			0, h);
		path.moveTo(poly.at(0));
		path.lineTo(poly.at(1));
		path.cubicTo(poly.at(2), poly.at(3), poly.at(4));
		path.lineTo(poly.at(5));
		if (iType == 3) x += w8;
	}
	// Band
	if (iType == 1) {
		const int y2 = (y + h4) >> 1;
		poly.putPoints(0, 6,
			0, h,
			x - w8 - ws, h,
			x - ws, y2,
			x + ws, y2,
			x + w8 + ws, h,
			0, h);
		path.moveTo(poly.at(0));
		path.lineTo(poly.at(1));
		path.cubicTo(poly.at(2), poly.at(3), poly.at(4));
		path.lineTo(poly.at(5));
	}
	// High, Notch
	if (iType == 2 || iType == 3) {
		if (iType == 3) { x += w8; y = h2; }
		poly.putPoints(0, 6,
			x - ws, h,
			x, y,
			x, h2,
			x + w8, h2,
			w, h2,
			w, h);
		path.moveTo(poly.at(0));
		path.cubicTo(poly.at(1), poly.at(2), poly.at(3));
		path.lineTo(poly.at(4));
		path.lineTo(poly.at(5));
		if (iType == 3) x -= w8;
	}
	// Formant
	if (iType == 4) {
		const int x2 = (x - w4) >> 2;
		const int y2 = (y - h4) >> 2;
		poly.putPoints(0, 6,
			0, h2,
			x2, h2,
			x - ws, h2,
			x, y2,
			x + ws, h,
			0, h);
		path.moveTo(poly.at(0));
	#if 0
		path.lineTo(poly.at(1));
		path.cubicTo(poly.at(2), poly.at(3), poly.at(4));
	#else
		const int n3 = 5; // num.formants
		const int w3 = (x + ws - x2) / n3 - 1;
		const int w6 = (w3 >> 1);
		const int h3 = (h4 >> 1);
		int x3 = x2; int y3 = y2;
		for (int i = 0; i < n3; ++i) {
			poly.putPoints(1, 3,
				x3, h2,
				x3 + w6, y3,
				x3 + w3, y3 + h2);
			path.cubicTo(poly.at(1), poly.at(2), poly.at(3));
			x3 += w3; y3 += h3;
		}
		path.lineTo(poly.at(4));
	#endif
		path.lineTo(poly.at(5));
	}

	const QPalette& pal = palette();
	const bool bDark = (pal.window().color().value() < 0x7f);
	const QColor& rgbLite = (isEnabled()
		? (bDark ? Qt::darkYellow : Qt::yellow) : pal.mid().color());
	const QColor& rgbDark = pal.window().color().darker(180);

	painter.fillRect(rect, rgbDark);

	painter.setPen(bDark ? Qt::gray : Qt::darkGray);

	QLinearGradient grad(0, 0, w << 1, h << 1);
	grad.setColorAt(0.0f, rgbLite);
	grad.setColorAt(1.0f, Qt::black);

	painter.setRenderHint(QPainter::Antialiasing, true);

	painter.setBrush(grad);
	painter.drawPath(path);

#ifdef CONFIG_DEBUG_0
	painter.drawText(QFrame::rect(),
		Qt::AlignTop|Qt::AlignHCenter,
		tr("Cutoff(%1) Reso(%2)")
		.arg(int(100.0f * cutoff()))
		.arg(int(100.0f * reso())));
#endif

	painter.setRenderHint(QPainter::Antialiasing, false);

	painter.end();

	QFrame::paintEvent(pPaintEvent);
}