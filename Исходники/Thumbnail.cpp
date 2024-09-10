void
Thumbnail::paintOverImage(
	QPainter& painter, QTransform const& image_to_display,
	QTransform const& thumb_to_display)
{	
	// We work in display coordinates because we want to be
	// pixel-accurate with what we draw.
	painter.setWorldTransform(QTransform());

	QTransform const virt_to_display(virtToThumb() * thumb_to_display);

	QRectF const inner_rect(virt_to_display.map(m_virtContentRect).boundingRect());
	
	// We extend the outer rectangle because otherwise we may get white
	// thin lines near the edges due to rounding errors and the lack
	// of subpixel accuracy.  Doing that is actually OK, because what
	// we paint will be clipped anyway.
	QRectF const outer_rect(
		virt_to_display.map(m_virtOuterRect).boundingRect().adjusted(-1.0, -1.0, 1.0, 1.0)
	);
	
	QPainterPath outer_outline;
	outer_outline.addPolygon(PolygonUtils::round(outer_rect));
	
	QPainterPath content_outline;
	content_outline.addPolygon(PolygonUtils::round(inner_rect));
	
	painter.setRenderHint(QPainter::Antialiasing, true);
	
	QColor bg_color;
	QColor fg_color;
	if (m_params.alignment().isNull()) {
		// "Align with other pages" is turned off.
		// Different color is useful on a thumbnail list to
		// distinguish "safe" pages from potentially problematic ones.
		bg_color = QColor(0x58, 0x7f, 0xf4, 70);
		fg_color = QColor(0x00, 0x52, 0xff);
	} else {
		bg_color = QColor(0xbb, 0x00, 0xff, 40);
		fg_color = QColor(0xbe, 0x5b, 0xec);
	}

	// Draw margins.
	painter.fillPath(outer_outline.subtracted(content_outline), bg_color);
	
	QPen pen(fg_color);
	pen.setCosmetic(true);
	pen.setWidthF(1.0);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
	
	// toRect() is necessary because we turn off antialiasing.
	// For some reason, if we let Qt round the coordinates,
	// the result is slightly different.
	painter.drawRect(inner_rect.toRect());
}