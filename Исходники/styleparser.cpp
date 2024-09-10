/**
 * Parse a single <TextStyle> element
 *
 * \return an ITextStyle representing the <TextStyle> element
 */
ITextStyle* StyleParser::parseTextStyleElement( QXmlStreamReader* xml ) {
    TextStyle* ts = new TextStyle();
    ts->setName( xml->attributes().value( "name" ).toString() );
    bool hAlign = false;
    bool vAlign = false;

    while ( !( xml->isEndElement() && ( xml->name() == "TextStyle" ) ) ) {
        xml->readNext();

        if ( xml->isStartElement() ) {
            if ( xml->name() == "Font" ) {
                ts->setFontName( xml->readElementText() );
            }

            if ( xml->name() == "Size" ) {
                ts->setPointSize( xml->readElementText().toInt() );
            }

            if ( xml->name() == "Bold" ) {
                ts->setBold( true );
            }

            if ( xml->name() == "Italic" ) {
                ts->setItalic( true );
            }

            if ( xml->name() == "Color" ) {
                int r = xml->attributes().value( "r" ).toString().toInt();
                int g = xml->attributes().value( "g" ).toString().toInt();
                int b = xml->attributes().value( "b" ).toString().toInt();
                int a = xml->attributes().value( "a" ).toString().toInt();
                ts->setForeColor( QColor( r, g, b, a ) );
                ts->setRgbaColorString( QString( "rgba(%1,%2,%3,%4)" ).arg( r )
                                        .arg( g )
                                        .arg( b )
                                        .arg( a ) );
            }

            if ( xml->name() == "HAlign" ) {
                QString a = xml->readElementText();
                hAlign = true;

                if ( a.toLower() == "left" )
                    ts->addAlignment( Qt::AlignLeft );
                else if ( a.toLower() == "right" )
                    ts->addAlignment( Qt::AlignRight );
                else if ( a.toLower() == "center" )
                    ts->addAlignment( Qt::AlignHCenter );
                else
                    hAlign = false;
            }

            if ( xml->name() == "VAlign" ) {
                QString a = xml->readElementText();
                vAlign = true;

                if ( a.toLower() == "top" )
                    ts->addAlignment( Qt::AlignTop );
                else if ( a.toLower() == "bottom" )
                    ts->addAlignment( Qt::AlignBottom );
                else if ( a.toLower() == "center" )
                    ts->addAlignment( Qt::AlignVCenter );
                else
                    vAlign = false;
            }
        }
    }

    //Set some default values
    if ( !hAlign )
        ts->addAlignment( Qt::AlignLeft );

    if ( !vAlign )
        ts->addAlignment( Qt::AlignTop );

    return ts;
}