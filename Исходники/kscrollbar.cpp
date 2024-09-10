QRect KScrollBar::subControlRect(QStyle::SubControl sc)
{
	QRect ret;
	const QRect scrollBarRect = QRect(QPoint(0, 0), size().toSize());
	int sbextent = m_buttonHeight;
	switch (sc)
	{
	case QStyle::SC_ScrollBarSubLine:            // top/left button
		if (m_orientation == Qt::Horizontal) 
		{
			int buttonWidth = qMin(scrollBarRect.width() / 2, sbextent);
			ret.setRect(0, 0, buttonWidth, scrollBarRect.height());
		} 
		else 
		{
			int buttonHeight = qMin(scrollBarRect.height() / 2, sbextent);
			ret.setRect(0, 0, scrollBarRect.width(), buttonHeight);
		}
		return ret;
	case QStyle::SC_ScrollBarAddLine:            // bottom/right button
		if (m_orientation == Qt::Horizontal) 
		{
			int buttonWidth = qMin(scrollBarRect.width()/2, sbextent);
			ret.setRect(scrollBarRect.width() - buttonWidth, 0, buttonWidth, scrollBarRect.height());
		} 
		else 
		{
			int buttonHeight = qMin(scrollBarRect.height()/2, sbextent);
			ret.setRect(0, scrollBarRect.height() - buttonHeight, scrollBarRect.width(), buttonHeight);
		}
		return ret;
	}
	int maxlen = ((m_orientation == Qt::Horizontal) ? width() : height()) - (sbextent * 2);
	int sliderlen = sliderPixels();
	int sliderstart = sbextent + sliderPositionFromValue(m_minimum, m_maximum, m_value, maxlen - sliderlen, false);
	switch (sc)
	{
	case QStyle::SC_ScrollBarSubPage:            // between top/left button and slider
		if (m_orientation == Qt::Horizontal)
			ret.setRect(sbextent, 0, sliderstart - sbextent, scrollBarRect.height());
		else
			ret.setRect(0, sbextent, scrollBarRect.width(), sliderstart - sbextent);
		break;
	case QStyle::SC_ScrollBarAddPage:            // between bottom/right button and slider
		if (m_orientation == Qt::Horizontal)
			ret.setRect(sliderstart + sliderlen, 0, maxlen - sliderstart - sliderlen + sbextent, scrollBarRect.height());
		else
			ret.setRect(0, sliderstart + sliderlen, scrollBarRect.width(), maxlen - sliderstart - sliderlen + sbextent);
		break;
	case QStyle::SC_ScrollBarGroove:
		if (m_orientation == Qt::Horizontal)
			ret.setRect(sbextent, 0, scrollBarRect.width() - sbextent * 2, scrollBarRect.height());
		else
			ret.setRect(0, sbextent, scrollBarRect.width(), scrollBarRect.height() - sbextent * 2);
		break;
	case QStyle::SC_ScrollBarSlider:
		if (m_orientation == Qt::Horizontal)
			ret.setRect(sliderstart, 0, sliderlen, scrollBarRect.height());
		else
			ret.setRect(0, sliderstart, scrollBarRect.width(), sliderlen);
		break;
	default:
		break;
	}
	return ret;
}