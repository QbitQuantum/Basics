void KBBLevelConfigurationPreview::drawBackground(QPainter* painter, const QRectF&)
{
	QRectF rectBackground;

	// TODO: This is duplication of code from the class KBBScalableGraphicWidget. Try to fix this.
	const qreal sW = scene()->width();
	const qreal sH = scene()->height();
	const qreal wW = width();
	const qreal wH = height();
	const qreal offset = (sH+sW)/100 ;
	if (sH*wW > sW*wH) {
		// The widget is larger than the scene
		qreal w =  wW*sH/wH;
		rectBackground.setRect((sW-w)/2-offset, -offset, w + 2*offset, sH + 2*offset);
	} else {
		// The scene is larger than the widget (or as large)
		qreal h =  wH*sW/wW;
		rectBackground.setRect(-offset, (sH-h)/2-offset, sW + 2*offset, h + 2*offset);
	}

	m_themeManager->svgRenderer()->render(painter, m_themeManager->elementId(KBBScalableGraphicWidget::background), rectBackground);
}