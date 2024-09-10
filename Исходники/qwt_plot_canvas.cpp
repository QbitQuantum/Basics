static void qwtFillBackground( QPainter *painter, 
    QWidget *widget, const QVector<QRectF> &fillRects )
{
    if ( fillRects.isEmpty() )
        return;

    QRegion clipRegion;
    if ( painter->hasClipping() )
        clipRegion = painter->transform().map( painter->clipRegion() );
    else
        clipRegion = widget->contentsRect();

    // Try to find out which widget fills
    // the unfilled areas of the styled background

    QWidget *bgWidget = qwtBackgroundWidget( widget->parentWidget() );

    for ( int i = 0; i < fillRects.size(); i++ )
    {
        const QRect rect = fillRects[i].toAlignedRect();
        if ( clipRegion.intersects( rect ) )
        {
            QPixmap pm( rect.size() );
            qwtFillPixmap( bgWidget, pm,
                widget->mapTo( bgWidget, rect.topLeft() ) );
            painter->drawPixmap( rect, pm );
        }
    }
}