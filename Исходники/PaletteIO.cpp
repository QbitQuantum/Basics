bool PaletteIO::read(Palettes &palettes) const
{
	if(!canRead()) {
		return false;
	}

	QByteArray palData = device()->read(12);

	if(palData.size() != 12) {
		qWarning() << "PaletteIO::read Pal size too short";
		return false;
	}

	quint16 palH;

	memcpy(&palH, palData.constData() + 10, 2);

	palData = device()->read(palH * 512);

	if(palData.size() != palH * 512) {
		qWarning() << "PaletteIO::read Pal size too short 2";
		return false;
	}

	for(quint32 i=0 ; i<palH ; ++i) {
		palettes.append(createPalette(palData.constData() + i*512));
	}

	return readAfter(palettes);
}