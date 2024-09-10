static void generate_qpath( mlt_properties producer_properties )
{
	QPainterPath* qPath = static_cast<QPainterPath*>( mlt_properties_get_data( producer_properties, "_qpath", NULL ) );
	int outline = mlt_properties_get_int( producer_properties, "outline" );
	char* align = mlt_properties_get( producer_properties, "align" );
	char* style = mlt_properties_get( producer_properties, "style" );
	char* text = mlt_properties_get( producer_properties, "text" );
	char* encoding = mlt_properties_get( producer_properties, "encoding" );
	int pad = mlt_properties_get_int( producer_properties, "pad" );
	int offset = pad + ( outline / 2 );
	int width = 0;
	int height = 0;

	// Make the path empty
	*qPath = QPainterPath();

	// Get the strings to display
	QTextCodec *codec = QTextCodec::codecForName( encoding );
	QTextDecoder *decoder = codec->makeDecoder();
	QString s = decoder->toUnicode( text );
	delete decoder;
	QStringList lines = s.split( "\n" );

	// Configure the font
	QFont font;
	font.setPixelSize( mlt_properties_get_int( producer_properties, "size" ) );
	font.setFamily( mlt_properties_get( producer_properties, "family" ) );
	font.setWeight( ( mlt_properties_get_int( producer_properties, "weight" ) / 10 ) -1 );
	switch( style[0] )
	{
	case 'i':
	case 'I':
		font.setStyle( QFont::StyleItalic );
		break;
	}
	QFontMetrics fm( font );

	// Determine the text rectangle size
	height = fm.lineSpacing() * lines.size();
	for( int i = 0; i < lines.size(); ++i )
	{
		int line_width = fm.width( lines.at(i) );
		if( line_width > width ) width = line_width;
	}

	// Lay out the text in the path
	int x = 0;
	int y = fm.ascent() + 1 + offset;
	for( int i = 0; i < lines.size(); ++i )
	{
		QString line = lines.at(i);
		x = offset;
		switch( align[0] )
		{
			default:
			case 'l':
			case 'L':
				break;
			case 'c':
			case 'C':
				x += ( width - fm.width( line ) ) / 2;
				break;
			case 'r':
			case 'R':
				x += width - fm.width( line );
				break;
		}
		qPath->addText( x, y, font, line );
		y += fm.lineSpacing();
	}

	// Account for outline and pad
	width += offset * 2;
	height += offset * 2;
	// Sanity check
	if( width == 0 ) width = 1;
	if( height == 0 ) height = 1;
	mlt_properties_set_int( producer_properties, "meta.media.width", width );
	mlt_properties_set_int( producer_properties, "meta.media.height", height );
}