void
PictureZoneEditor::onPaint(QPainter& painter, InteractionState const& interaction)
{
	painter.setWorldTransform(QTransform());
	painter.setRenderHint(QPainter::Antialiasing);

	if (!validateScreenPictureMask()) {
		schedulePictureMaskRebuild();
	} else {
		double const sn = sin(constants::DEG2RAD * m_pictureMaskAnimationPhase);
		double const scale = 0.5 * (sn + 1.0); // 0 .. 1
		double const opacity = 0.35 * scale + 0.15;

		QPixmap mask(m_screenPictureMask);

		{
			QPainter mask_painter(&mask);
			mask_painter.translate(-m_screenPictureMaskOrigin);
			paintOverPictureMask(mask_painter);
		}

		painter.setOpacity(opacity);
		painter.drawPixmap(m_screenPictureMaskOrigin, mask);
		painter.setOpacity(1.0);

		if (!m_pictureMaskAnimateTimer.isActive()) {
			m_pictureMaskAnimateTimer.start();
		}
	}
}