void QwtScaleWidget::drawTitle( QPainter *painter,
    QwtScaleDraw::Alignment align, const QRectF &rect ) const
{
    QRectF r = rect;
    double angle;
    int flags = d_data->title.renderFlags() &
        ~( Qt::AlignTop | Qt::AlignBottom | Qt::AlignVCenter );

    switch ( align )
    {
        case QwtScaleDraw::LeftScale:
            angle = -90.0;
            flags |= Qt::AlignTop;
            r.setRect( r.left(), r.bottom(),
                r.height(), r.width() - d_data->titleOffset );
            break;

        case QwtScaleDraw::RightScale:
            angle = -90.0;
            flags |= Qt::AlignTop;
            r.setRect( r.left() + d_data->titleOffset, r.bottom(),
                r.height(), r.width() - d_data->titleOffset );
            break;

        case QwtScaleDraw::BottomScale:
            angle = 0.0;
            flags |= Qt::AlignBottom;
            r.setTop( r.top() + d_data->titleOffset );
            break;

        case QwtScaleDraw::TopScale:
        default:
            angle = 0.0;
            flags |= Qt::AlignTop;
            r.setBottom( r.bottom() - d_data->titleOffset );
            break;
    }

    if ( d_data->layoutFlags & TitleInverted )
    {
        if ( align == QwtScaleDraw::LeftScale
            || align == QwtScaleDraw::RightScale )
        {
            angle = -angle;
            r.setRect( r.x() + r.height(), r.y() - r.width(),
                r.width(), r.height() );
        }
    }

    painter->save();
    painter->setFont( font() );
    painter->setPen( palette().color( QPalette::Text ) );

    painter->translate( r.x(), r.y() );
    if ( angle != 0.0 )
        painter->rotate( angle );

    QwtText title = d_data->title;
    title.setRenderFlags( flags );
    title.draw( painter, QRectF( 0.0, 0.0, r.width(), r.height() ) );

    painter->restore();
}