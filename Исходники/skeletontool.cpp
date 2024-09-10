void SkeletonTool::drawDrawingBrowser(const TXshCell &cell, const TPointD &center)
{
	if (!cell.m_level || cell.m_level->getFrameCount() <= 1)
		return;
	double pixelSize = getPixelSize();

	std::string name = ::to_string(cell.m_level->getName()) + "." + std::to_string(cell.m_frameId.getNumber());

	QString qText = QString::fromStdString(name);
	QFont font("Arial", 10); // ,QFont::Bold);
	QFontMetrics fm(font);
	QSize textSize = fm.boundingRect(qText).size();
	int arrowHeight = 10;
	int minTextWidth = 2 * arrowHeight + 5;
	if (textSize.width() < minTextWidth)
		textSize.setWidth(minTextWidth);
	QSize totalSize(textSize.width(), textSize.height() + 2 * arrowHeight);
	TPointD p = center + TPointD(30, -arrowHeight) * pixelSize;
	QRect textRect(0, arrowHeight, textSize.width(), textSize.height());

	assert(glGetError() == 0);

	if (isPicking()) {
		double x0 = p.x, x1 = p.x + totalSize.width() * pixelSize;
		double y0 = p.y, y3 = p.y + totalSize.height() * pixelSize;
		double y1 = y0 + arrowHeight * pixelSize;
		double y2 = y3 - arrowHeight * pixelSize;
		double x = (x0 + x1) * 0.5;
		double d = arrowHeight * pixelSize;

		glColor3d(0, 1, 0);
		glPushName(TD_ChangeDrawing);
		glRectd(x0, y1, x1, y2);
		glPopName();
		glPushName(TD_IncrementDrawing);
		glBegin(GL_POLYGON);
		glVertex2d(x, y0);
		glVertex2d(x + d, y0 + d);
		glVertex2d(x - d, y0 + d);
		glEnd();
		glPopName();
		glPushName(TD_DecrementDrawing);
		glBegin(GL_POLYGON);
		glVertex2d(x, y3);
		glVertex2d(x + d, y3 - d);
		glVertex2d(x - d, y3 - d);
		glEnd();
		glPopName();
		return;
	} else {

		assert(glGetError() == 0);
		bool active = m_device == TD_ChangeDrawing || m_device == TD_IncrementDrawing || m_device == TD_DecrementDrawing;
		QImage img(totalSize.width(), totalSize.height(), QImage::Format_ARGB32);
		img.fill(Qt::transparent);
		QPainter imgPainter(&img);
		imgPainter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

		//imgPainter.setPen(Qt::black);
		//imgPainter.drawRect(0,0,totalSize.width(),totalSize.height());

		imgPainter.setPen(Qt::NoPen);
		imgPainter.setBrush(QColor(200, 200, 200, 200));
		imgPainter.drawRect(textRect);
		imgPainter.setPen(active ? Qt::red : Qt::black);
		imgPainter.setBrush(Qt::NoBrush);
		imgPainter.setFont(font);
		imgPainter.drawText(textRect, Qt::AlignCenter, qText);

		if (active) {
			int x = textRect.center().x();
			int d = arrowHeight - 4;
			int y = 0;
			QPainterPath upArrow;
			upArrow.moveTo(x, y);
			upArrow.lineTo(x + d, y + d);
			upArrow.lineTo(x - d, y + d);
			upArrow.lineTo(x, y);
			y = totalSize.height() - 1;
			QPainterPath dnArrow;
			dnArrow.moveTo(x, y);
			dnArrow.lineTo(x + d, y - d);
			dnArrow.lineTo(x - d, y - d);
			dnArrow.lineTo(x, y);

			imgPainter.setPen(Qt::NoPen);
			imgPainter.setBrush(m_device == TD_DecrementDrawing ? QColor(255, 0, 0) : QColor(200, 100, 100));
			imgPainter.drawPath(upArrow);
			imgPainter.setBrush(m_device == TD_IncrementDrawing ? QColor(255, 0, 0) : QColor(200, 100, 100));
			imgPainter.drawPath(dnArrow);
		}

		QImage texture = QGLWidget::convertToGLFormat(img);

		glRasterPos2f(p.x, p.y);
		// glBitmap(0,0,0,0,  0,-size.height()+(y+delta.y),  NULL); //
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawPixels(texture.width(), texture.height(), GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
		glDisable(GL_BLEND);
		glColor3d(0, 0, 0);

		assert(glGetError() == 0);
	}
}