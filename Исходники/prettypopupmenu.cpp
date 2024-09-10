void
PrettyPopupMenu::paintEvent( QPaintEvent* e )
{
    generateSidePixmap();

    QPainter p( this );

    QRect r = sideImageRect();
    r.setTop( r.bottom() - s_sidePixmap.height() );
    if ( r.intersects( e->rect() ) )
    {
        QRect drawRect = r.intersect( e->rect() ).intersect( sideImageRect() );
        QRect pixRect = drawRect;
        pixRect.moveBy( -r.left(), -r.top() );
        p.drawImage( drawRect.topLeft(), s_sidePixmap, pixRect );
    }

    p.setClipRegion( e->region() );


    //NOTE The order is important here. drawContents() must be called before drawPrimitive(),
    //     otherwise we get rendering glitches.

    drawContents( &p );

    style().drawPrimitive( QStyle::PE_PanelPopup, &p,
                           QRect( 0, 0, width(), height() ),
                           colorGroup(), QStyle::Style_Default,
                           QStyleOption( frameWidth(), 0 ) );
}