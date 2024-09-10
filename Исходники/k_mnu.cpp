void PanelKMenu::paintEvent(QPaintEvent * e)
{
    if (sidePixmap.isNull()) {
        PanelServiceMenu::paintEvent(e);
        return;
    }

    QPainter p(this);
    p.setClipRegion(e->region());

    QStyleOptionFrame frOpt;
    frOpt.init(this);
    frOpt.lineWidth    = frameWidth();
    frOpt.midLineWidth = 0;
    style()->drawPrimitive( QStyle::PE_FrameMenu, &frOpt, &p, this);

    QRect r = sideImageRect();
    r.setBottom( r.bottom() - sidePixmap.height() );
    if ( r.intersects( e->rect() ) )
    {
        p.drawTiledPixmap( r, sideTilePixmap );
    }

    r = sideImageRect();
    r.setTop( r.bottom() - sidePixmap.height() );
    if ( r.intersects( e->rect() ) )
    {
        QRect drawRect = r.intersect( e->rect() );
        QRect pixRect = drawRect;
        pixRect.translate( -r.left(), -r.top() );
        p.drawPixmap( drawRect.topLeft(), sidePixmap, pixRect );
    }

    PanelServiceMenu::paintEvent( e );
}