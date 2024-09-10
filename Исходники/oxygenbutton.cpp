    //___________________________________________________
    void Button::paint( QPainter& painter )
    {

        QPalette palette( _client.palette() );
        palette.setCurrentColorGroup( isActive() ? QPalette::Active : QPalette::Inactive);

        if(
            _client.compositingActive() &&
            !( _client.isMaximized() || _type == ButtonItemClose || _type == ButtonItemMenu ) )
        { painter.translate( 0, -1 ); }

        // translate buttons down if window maximized
        if( _client.isMaximized() ) painter.translate( 0, 1 );

        // base button color
        QColor base;
        if( _type == ButtonItemClose && _forceInactive ) base = _client.backgroundPalette( this, palette ).window().color();
        else if( _type == ButtonItemClose ) base = palette.window().color();
        else base = palette.button().color();

        // text color
        QColor color = (_type == ButtonItemClose && _forceInactive ) ?
            buttonDetailColor( _client.backgroundPalette( this, palette ) ):
            buttonDetailColor( palette );

        // decide decoration color
        QColor glow;
        if( isAnimated() || (_status&Hovered) )
        {
            glow = isCloseButton() ?
                _helper.viewNegativeTextBrush().brush(palette).color():
                _helper.viewHoverBrush().brush(palette).color();

            if( isAnimated() )
            {

                color = KColorUtils::mix( color, glow, glowIntensity() );
                glow = _helper.alphaColor( glow, glowIntensity() );

            } else if( _status&Hovered  ) color = glow;

        }

        if( hasDecoration() )
        {
            // scale
            qreal scale( (21.0*_client.buttonSize())/22.0 );

            // pressed state
            const bool pressed(
                (_status&Pressed) ||
                ( _type == ButtonSticky && _client.isOnAllDesktops()  ) ||
                ( _type == ButtonAbove && _client.keepAbove() ) ||
                ( _type == ButtonBelow && _client.keepBelow() ) );

            // draw button shape
            painter.drawPixmap(0, 0, _helper.windecoButton( base, glow, pressed, scale ) );

        }

        // Icon
        // for menu button the application icon is used
        if( isMenuButton() )
        {

            int iconScale( 0 );
            switch( _client.buttonSize() )
            {
                case Configuration::ButtonSmall: iconScale = 13; break;

                default:
                case Configuration::ButtonDefault: iconScale = 16; break;
                case Configuration::ButtonLarge: iconScale = 20; break;
                case Configuration::ButtonVeryLarge: iconScale = 24; break;
                case Configuration::ButtonHuge: iconScale = 35; break;
            }

            const QPixmap& pixmap( _client.icon().pixmap( iconScale ) );
            const double offset = 0.5*(width()-pixmap.width() );
            painter.drawPixmap(offset, offset-1, pixmap );

        } else {

            painter.setRenderHints(QPainter::Antialiasing);
            qreal width( 1.2 );

            // contrast
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen( _helper.calcLightColor( base ), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            drawIcon(&painter);

            // main
            painter.translate(0,-1.5);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(color, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            drawIcon(&painter);

        }

    }