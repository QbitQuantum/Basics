void KDoor::drawCurImageEffect(QPainter &painter,const QImage &curImage, const float& frame)
{
	float switchAreaWidth = curImage.width();
	float switchAreaHeight = curImage.height();

	float offsetWide = (switchAreaWidth * 0.6) / 2;
	float offsetHeight = (switchAreaHeight * 0.6) / 2;

	//计算当前image增长的大小
	float m_fIncreasedWidth = offsetWide * frame;
	float m_fIncreasedHeight = offsetHeight * frame;
	QImage image = curImage.scaled(switchAreaWidth * 0.4 + m_fIncreasedWidth * 2,
		switchAreaHeight * 0.4 + m_fIncreasedHeight * 2);

	QPointF widgetCenter = curImage.rect().center();

	painter.save();

	QRectF rectF(widgetCenter.x() - image.width() / 2,
		widgetCenter.y() - image.height() / 2, image.width(), image.height());
	painter.drawImage(rectF,image);

	painter.restore();
}