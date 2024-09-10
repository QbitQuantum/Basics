QVariant CharTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || m_doc == 0)
		return QVariant();

	int ix = index.row() * m_cols + index.column();
	uint currentChar;
	QString currentFont = m_fontInUse;
	if (ix < m_characters.count())
	{
		currentChar = m_characters[ix];
		currentFont = m_fonts[ix];
	}
	else
		return QVariant();

	// for mimeData()
	if (role == CharTableModel::CharTextRole)
		return QString("%1").arg(QChar(currentChar));

	if (role == CharTableModel::CharTextAndFontRole)
		return QString("%1#%2").arg(currentChar).arg(currentFont);

	// tooltip
	if (role == Qt::ToolTipRole)
		return QString("Unicode:\n0x%1").arg(currentChar, 4, 16, QChar('0'));

	// status tip
	if ( role == Qt::StatusTipRole )
	{
		QString tmp = QString("%1").arg(currentChar, 4, 16, QChar('0')).toUpper();
		QStringList lst;
		lst << tmp << currentFont;
		return lst;
	}

	// pixmap
	if (role == Qt::DecorationRole)
	{
		// m_cols should not become 0. Never.
		int baseSize = m_viewWidth / m_cols;
		QTransform chma;
		chma.scale(baseSize/10, baseSize/10);

		ScFace face = (*m_doc->AllFonts)[currentFont];
		uint gl = face.char2CMap(currentChar);
		int size = baseSize + qRound(-face.descent() * baseSize) + 1;
		double ww = baseSize - face.glyphWidth(gl, baseSize);

		QImage pix(baseSize, size, QImage::Format_ARGB32_Premultiplied);
		ScPainter *p = new ScPainter(&pix, baseSize, size);
		p->clear();
		FPointArray gly = face.glyphOutline(gl, 1);
		if (gly.size() > 4)
		{
			gly.map(chma);
			p->translate(ww / 2, 1);
			p->setBrush(Qt::black);
			p->setFillMode(1);
			p->setupPolygon(&gly);
			p->fillPath();
			p->end();
		}
		delete p;
		return QVariant(QPixmap::fromImage(pix));
	}
	// trash
	return QVariant();
}