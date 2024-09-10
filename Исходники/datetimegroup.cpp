void DateTimeGroup::configChanged()
{
	
	KConfigGroup cg = config();

	if (isUserConfiguring()) {
		configAccepted();
	}
	m_natoOperation = cg.readEntry("natoOperation", m_natoOperation);
	m_local= cg.readEntry("localTime", m_local);

	QFont f = cg.readEntry("plainDateTimeGroupFont", m_plainDateTimeGroupFont);
	m_isDefaultFont = f == m_plainDateTimeGroupFont;
	m_plainDateTimeGroupFont = f;
	
	m_useCustomColor = cg.readEntry("useCustomColor", m_useCustomColor);
	m_plainDateTimeGroupColor = cg.readEntry("plainDateTimeGroupColor", m_plainDateTimeGroupColor);
	m_useCustomShadowColor = cg.readEntry("useCustomShadowColor", m_useCustomShadowColor);
	m_plainDateTimeGroupShadowColor = cg.readEntry("plainDateTimeGroupShadowColor", m_plainDateTimeGroupShadowColor);
	
	m_drawShadow = cg.readEntry("plainDateTimeGroupDrawShadow", m_drawShadow);
	m_rounded=cg.readEntry("rounded",m_rounded);
	m_format=cg.readEntry("format",m_format);
	
	m_showSeconds=m_format==2;
	if (m_showSeconds) {
		//We don't need to cache the applet if it update every seconds
		setCacheMode(QGraphicsItem::NoCache);
	} else {
		setCacheMode(QGraphicsItem::DeviceCoordinateCache);
	}
	
	m_sAfterDay =cg.readEntry("sAfterDay", m_sAfterDay);
	m_sAfterHour = cg.readEntry("sAfterHour", m_sAfterHour);
	m_sAfterMinute = cg.readEntry("sAfterMinute", m_sAfterMinute);
	
	m_sAfterSecond = cg.readEntry("sAfterSecond", m_sAfterSecond);
	m_sAfterTimeZone = cg.readEntry("sAfterTimeZone", m_sAfterTimeZone);
	m_sAfterMonth = cg.readEntry("sAfterMonth", m_sAfterMonth);
	
	updateColors();
	
	if (m_useCustomColor) {
		m_pixmap = QPixmap();
		delete m_svg;
		m_svg = 0;
	}
	
	const QFontMetricsF metrics(KGlobalSettings::smallestReadableFont());
	setMinimumSize(metrics.size(Qt::TextSingleLine, dtg));
	updateSize();
}