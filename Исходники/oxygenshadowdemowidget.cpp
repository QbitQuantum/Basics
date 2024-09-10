    //______________________________________
    void ShadowDemoWidget::updateBackgroundPixmap( void )
    {

        // check if background pixmap needs update
        QRect backgroundRect( QPoint( 0, 0 ), size() - QSize( 2*_shadowSize, 2*_shadowSize )  );
        if( !_backgroundPixmap.isNull() && _backgroundPixmap.size() == backgroundRect.size() )
        { return; }

        _backgroundPixmap = QPixmap( backgroundRect.size() );
        _backgroundPixmap.fill( Qt::transparent );
        QPainter painter( &_backgroundPixmap );
        painter.setRenderHint( QPainter::Antialiasing );

        _dummy.resize( backgroundRect.size() );
        helper().renderWindowBackground(
            &painter, backgroundRect,
            &_dummy, &_dummy, palette().color( QPalette::Window ), 0, 64 );

        // float frame
        helper().drawFloatFrame( &painter, backgroundRect.adjusted( -1, -1, 1, 1 ), palette().color( QPalette::Window ), false );

        // add rounded mask
        painter.save();
        painter.setCompositionMode( QPainter::CompositionMode_DestinationIn );
        painter.setBrush( Qt::black );
        painter.setPen( Qt::NoPen );
        if( _square )
        {
            QRectF rectF( backgroundRect );
            QPainterPath path;

            // rotate counterclockwise, cause that makes angles easier
            path.moveTo( rectF.topLeft() + QPointF( 3.5, 0 ) );
            path.arcTo( QRectF( rectF.topLeft(), QSize( 7, 7 ) ), 90, 90 );
            path.lineTo( rectF.bottomLeft() );
            path.lineTo( rectF.bottomRight() );
            path.lineTo( rectF.topRight() + QPointF( 0, 3.5 ) );
            path.arcTo( QRectF( rectF.topRight() + QPointF( -7, 0 ), QSize( 7, 7 ) ), 0, 90 );
            path.lineTo( rectF.topLeft() + QPointF( 3.5, 0 ) );
            painter.drawPath( path );

        } else {

            painter.drawRoundedRect( QRectF( backgroundRect ), 3.5, 3.5 );

        }

        painter.restore();
    }