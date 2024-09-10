void
IncompleteThumbnail::drawQuestionMark(QPainter& painter, QRectF const& bounding_rect)
{
	QString const text(QString::fromAscii("?"));
	
	// Because painting happens only from the main thread, we don't
	// need to care about concurrent access.
	if (m_sCachedPath.isEmpty()) {
#if 0
		QFont font(painter.font());
		font.setWeight(QFont::DemiBold);
		font.setStyleStrategy(QFont::ForceOutline);
		m_sCachedPath.addText(0, 0, font, text);
#else
		m_sCachedPath.moveTo(QPointF(4.42188, -2.40625));
		m_sCachedPath.cubicTo(
			QPointF(4.42188, -3.20312),
			QPointF(4.51562, -3.32812),
			QPointF(5.23438, -3.84375)
		);
		m_sCachedPath.cubicTo(
			QPointF(6.34375, -4.625),
			QPointF(6.67188, -5.15625),
			QPointF(6.67188, -6.17188)
		);
		m_sCachedPath.cubicTo(
			QPointF(6.67188, -7.79688),
			QPointF(5.4375, -8.92188),
			QPointF(3.6875, -8.92188)
		);
		m_sCachedPath.cubicTo(
			QPointF(2.65625, -8.92188),
			QPointF(1.84375, -8.5625),
			QPointF(1.32812, -7.85938)
		);
		m_sCachedPath.cubicTo(
			QPointF(0.9375, -7.32812),
			QPointF(0.78125, -6.75),
			QPointF(0.765625, -5.76562)
		);
		m_sCachedPath.lineTo(QPointF(2.40625, -5.76562));
		m_sCachedPath.lineTo(QPointF(2.40625, -5.79688));
		m_sCachedPath.cubicTo(
			QPointF(2.34375, -6.76562),
			QPointF(2.92188, -7.51562),
			QPointF(3.71875, -7.51562)
		);
		m_sCachedPath.cubicTo(
			QPointF(4.4375, -7.51562),
			QPointF(4.98438, -6.90625),
			QPointF(4.98438, -6.125)
		);
		m_sCachedPath.cubicTo(
			QPointF(4.98438, -5.59375),
			QPointF(4.82812, -5.35938),
			QPointF(4.125, -4.78125)
		);
		m_sCachedPath.cubicTo(
			QPointF(3.17188, -3.96875),
			QPointF(2.90625, -3.4375),
			QPointF(2.9375, -2.40625)
		);
		m_sCachedPath.lineTo(QPointF(4.42188, -2.40625));
		m_sCachedPath.moveTo(QPointF(4.625, -1.75));
		m_sCachedPath.lineTo(QPointF(2.8125, -1.75));
		m_sCachedPath.lineTo(QPointF(2.8125, 0.0));
		m_sCachedPath.lineTo(QPointF(4.625, 0.0));
		m_sCachedPath.lineTo(QPointF(4.625, -1.75));
#endif
	}
	
	QRectF const text_rect(m_sCachedPath.boundingRect());
	
	QTransform xform1;
	xform1.translate(-text_rect.left(), -text_rect.top());
	
	QSizeF const unscaled_size(text_rect.size());
	QSizeF scaled_size(unscaled_size);
	scaled_size.scale(bounding_rect.size() * 0.9, Qt::KeepAspectRatio);
	
	double const hscale = scaled_size.width() / unscaled_size.width();
	double const vscale = scaled_size.height() / unscaled_size.height();
	QTransform xform2;
	xform2.scale(hscale, vscale);
	
	// Position the text at the center of our bounding rect.
	QSizeF const translation(bounding_rect.size() * 0.5 - scaled_size * 0.5);
	QTransform xform3;
	xform3.translate(translation.width(), translation.height());
	
	painter.setWorldTransform(xform1 * xform2 * xform3, true);
	painter.setRenderHint(QPainter::Antialiasing);
	
	QPen pen(QColor(0x00, 0x00, 0x00, 60));
	pen.setWidth(2);
	pen.setCosmetic(true);
	painter.setPen(pen);
	
	painter.drawPath(m_sCachedPath);
}