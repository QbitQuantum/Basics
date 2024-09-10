void QLCDNumber::drawSegment( const QPoint &pos, char segmentNo, QPainter &p,
			      int segLen, bool erase )
{
    QPoint pt = pos;
    int width = segLen/5;

    const QColorGroup & g = colorGroup();
    QColor lightColor,darkColor,fgColor;
    if ( erase ){
	lightColor = backgroundColor();
	darkColor  = lightColor;
	fgColor    = lightColor;
    } else {
	lightColor = g.light();
	darkColor  = g.dark();
	fgColor    = g.foreground();
    }

#define LINETO(X,Y) addPoint( a, QPoint(pt.x() + (X),pt.y() + (Y)))
#define LIGHT
#define DARK

    if ( fill ) {
	QPointArray a(0);

	//The following is an exact copy of the switch below.
	//don't make any changes here
	switch ( segmentNo ) {
	case 0 :
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(segLen - 1,0);
	    DARK;
	    LINETO(segLen - width - 1,width);
	    LINETO(width,width);
	    LINETO(0,0);
	    break;
	case 1 :
	    pt += QPoint(0 , 1);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,width);
	    DARK;
	    LINETO(width,segLen - width/2 - 2);
	    LINETO(0,segLen - 2);
	    LIGHT;
	    LINETO(0,0);
	    break;
	case 2 :
	    pt += QPoint(segLen - 1 , 1);
	    p.moveTo(pt);
	    DARK;
	    LINETO(0,segLen - 2);
	    LINETO(-width,segLen - width/2 - 2);
	    LIGHT;
	    LINETO(-width,width);
	    LINETO(0,0);
	    break;
	case 3 :
	    pt += QPoint(0 , segLen);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,-width/2);
	    LINETO(segLen - width - 1,-width/2);
	    LINETO(segLen - 1,0);
	    DARK;
	    if (width & 1) {		// adjust for integer division error
		LINETO(segLen - width - 3,width/2 + 1);
		LINETO(width + 2,width/2 + 1);
	    } else {
		LINETO(segLen - width - 1,width/2);
		LINETO(width,width/2);
	    }
	    LINETO(0,0);
	    break;
	case 4 :
	    pt += QPoint(0 , segLen + 1);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,width/2);
	    DARK;
	    LINETO(width,segLen - width - 2);
	    LINETO(0,segLen - 2);
	    LIGHT;
	    LINETO(0,0);
	    break;
	case 5 :
	    pt += QPoint(segLen - 1 , segLen + 1);
	    p.moveTo(pt);
	    DARK;
	    LINETO(0,segLen - 2);
	    LINETO(-width,segLen - width - 2);
	    LIGHT;
	    LINETO(-width,width/2);
	    LINETO(0,0);
	    break;
	case 6 :
	    pt += QPoint(0 , segLen*2);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,-width);
	    LINETO(segLen - width - 1,-width);
	    LINETO(segLen - 1,0);
	    DARK;
	    LINETO(0,0);
	    break;
	case 7 :
	    if ( smallPoint )	// if smallpoint place'.' between other digits
		pt += QPoint(segLen + width/2 , segLen*2);
	    else
		pt += QPoint(segLen/2 , segLen*2);
	    p.moveTo(pt);
	    DARK;
	    LINETO(width,0);
	    LINETO(width,-width);
	    LIGHT;
	    LINETO(0,-width);
	    LINETO(0,0);
	    break;
	case 8 :
	    pt += QPoint(segLen/2 - width/2 + 1 , segLen/2 + width);
	    p.moveTo(pt);
	    DARK;
	    LINETO(width,0);
	    LINETO(width,-width);
	    LIGHT;
	    LINETO(0,-width);
	    LINETO(0,0);
	    break;
	case 9 :
	    pt += QPoint(segLen/2 - width/2 + 1 , 3*segLen/2 + width);
	    p.moveTo(pt);
	    DARK;
	    LINETO(width,0);
	    LINETO(width,-width);
	    LIGHT;
	    LINETO(0,-width);
	    LINETO(0,0);
	    break;
#if defined(CHECK_RANGE)
	default :
	    qWarning( "QLCDNumber::drawSegment: (%s) Internal error."
		     "  Illegal segment id: %d\n",
		     name( "unnamed" ), segmentNo );
#endif
	}
	// End exact copy
	p.setPen( fgColor );
	p.setBrush( fgColor );
	p.drawPolygon( a );
	p.setBrush( NoBrush );

	pt = pos;
    }
#undef LINETO
#undef LIGHT
#undef DARK

#define LINETO(X,Y) p.lineTo(QPoint(pt.x() + (X),pt.y() + (Y)))
#define LIGHT p.setPen(lightColor)
#define DARK  p.setPen(darkColor)
    if ( shadow )
	switch ( segmentNo ) {
	case 0 :
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(segLen - 1,0);
	    DARK;
	    LINETO(segLen - width - 1,width);
	    LINETO(width,width);
	    LINETO(0,0);
	    break;
	case 1 :
	    pt += QPoint(0,1);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,width);
	    DARK;
	    LINETO(width,segLen - width/2 - 2);
	    LINETO(0,segLen - 2);
	    LIGHT;
	    LINETO(0,0);
	    break;
	case 2 :
	    pt += QPoint(segLen - 1 , 1);
	    p.moveTo(pt);
	    DARK;
	    LINETO(0,segLen - 2);
	    LINETO(-width,segLen - width/2 - 2);
	    LIGHT;
	    LINETO(-width,width);
	    LINETO(0,0);
	    break;
	case 3 :
	    pt += QPoint(0 , segLen);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,-width/2);
	    LINETO(segLen - width - 1,-width/2);
	    LINETO(segLen - 1,0);
	    DARK;
	    if (width & 1) {		// adjust for integer division error
		LINETO(segLen - width - 3,width/2 + 1);
		LINETO(width + 2,width/2 + 1);
	    } else {
		LINETO(segLen - width - 1,width/2);
		LINETO(width,width/2);
	    }
	    LINETO(0,0);
	    break;
	case 4 :
	    pt += QPoint(0 , segLen + 1);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,width/2);
	    DARK;
	    LINETO(width,segLen - width - 2);
	    LINETO(0,segLen - 2);
	    LIGHT;
	    LINETO(0,0);
	    break;
	case 5 :
	    pt += QPoint(segLen - 1 , segLen + 1);
	    p.moveTo(pt);
	    DARK;
	    LINETO(0,segLen - 2);
	    LINETO(-width,segLen - width - 2);
	    LIGHT;
	    LINETO(-width,width/2);
	    LINETO(0,0);
	    break;
	case 6 :
	    pt += QPoint(0 , segLen*2);
	    p.moveTo(pt);
	    LIGHT;
	    LINETO(width,-width);
	    LINETO(segLen - width - 1,-width);
	    LINETO(segLen - 1,0);
	    DARK;
	    LINETO(0,0);
	    break;
	case 7 :
	    if ( smallPoint )	// if smallpoint place'.' between other digits
		pt += QPoint(segLen + width/2 , segLen*2);
	    else
		pt += QPoint(segLen/2 , segLen*2);
	    p.moveTo(pt);
	    DARK;
	    LINETO(width,0);
	    LINETO(width,-width);
	    LIGHT;
	    LINETO(0,-width);
	    LINETO(0,0);
	    break;
	case 8 :
	    pt += QPoint(segLen/2 - width/2 + 1 , segLen/2 + width);
	    p.moveTo(pt);
	    DARK;
	    LINETO(width,0);
	    LINETO(width,-width);
	    LIGHT;
	    LINETO(0,-width);
	    LINETO(0,0);
	    break;
	case 9 :
	    pt += QPoint(segLen/2 - width/2 + 1 , 3*segLen/2 + width);
	    p.moveTo(pt);
	    DARK;
	    LINETO(width,0);
	    LINETO(width,-width);
	    LIGHT;
	    LINETO(0,-width);
	    LINETO(0,0);
	    break;
#if defined(CHECK_RANGE)
	default :
	    qWarning( "QLCDNumber::drawSegment: (%s) Internal error."
		     "  Illegal segment id: %d\n",
		     name( "unnamed" ), segmentNo );
#endif
	}

#undef LINETO
#undef LIGHT
#undef DARK
}