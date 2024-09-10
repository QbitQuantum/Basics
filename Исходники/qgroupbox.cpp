void QGroupBox::paintEvent( QPaintEvent *event )
{
    QPainter paint( this );

    if ( lenvisible && !isCheckable() ) {	// draw title
        QFontMetrics fm = paint.fontMetrics();
        int h = fm.height();
        int tw = fm.width( str, lenvisible ) + fm.width(QChar(' '));
        int x;
        int marg = bFlat ? 0 : 8;
        if ( align & AlignHCenter )		// center alignment
            x = frameRect().width()/2 - tw/2;
        else if ( align & AlignRight )	// right alignment
            x = frameRect().width() - tw - marg;
        else if ( align & AlignLeft )		 // left alignment
            x = marg;
        else { // auto align
            if( QApplication::reverseLayout() )
                x = frameRect().width() - tw - marg;
            else
                x = marg;
        }
        QRect r( x, 0, tw, h );
        int va = style().styleHint(QStyle::SH_GroupBox_TextLabelVerticalAlignment, this);
        if(va & AlignTop)
            r.moveBy(0, fm.descent());
        QColor pen( (QRgb) style().styleHint(QStyle::SH_GroupBox_TextLabelColor, this )  );
        if (!style().styleHint(QStyle::SH_UnderlineAccelerator, this))
            va |= NoAccel;
        style().drawItem( &paint, r, ShowPrefix | AlignHCenter | va, colorGroup(),
                          isEnabled(), 0, str, -1, ownPalette() ? 0 : &pen );
        paint.setClipRegion( event->region().subtract( r ) ); // clip everything but title
#ifndef QT_NO_CHECKBOX
    } else if ( d->checkbox ) {
        QRect cbClip = d->checkbox->geometry();
        QFontMetrics fm = paint.fontMetrics();
        cbClip.setX( cbClip.x() - fm.width(QChar(' ')) );
        cbClip.setWidth( cbClip.width() + fm.width(QChar(' ')) );
        paint.setClipRegion( event->region().subtract( cbClip ) );
#endif
    }
    if ( bFlat ) {
        QRect fr = frameRect();
        QPoint p1( fr.x(), fr.y() + 1 );
        QPoint p2( fr.x() + fr.width(), p1.y() );
        // ### This should probably be a style primitive.
        qDrawShadeLine( &paint, p1, p2, colorGroup(), TRUE,
                        lineWidth(), midLineWidth() );
    } else {
        drawFrame(&paint);
    }
    drawContents( &paint );			// draw the contents
}