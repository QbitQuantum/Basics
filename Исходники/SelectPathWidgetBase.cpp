QToolButton* SelectPathWidgetBase::CreateToolButton(const DAVA::String& iconPath)
{
	QToolButton* retButton;
	
	retButton = new QToolButton(this);
	QIcon icon(iconPath.c_str());
	retButton->setIcon(icon);
	retButton->setCursor(Qt::ArrowCursor);
	retButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
	int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	QSize msz = minimumSizeHint();
	setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(retButton->sizeHint().width() * 2 + frameWidth));
	setMinimumSize(qMax(msz.width(), retButton->sizeHint().height() + frameWidth * 2 + 2),
				   qMax(msz.height(), retButton->sizeHint().height() + frameWidth * 2 + 2));
	
	return retButton;
}