void AVTPlotWidget::paintEvent( QPaintEvent *e ) {
    Q_UNUSED(e)

    QPainter p;

    p.begin( this );
    p.setRenderHint( QPainter::Antialiasing, antialiasing() );
    p.fillRect( rect(), backgroundColor() );
    p.translate( leftPadding(), topPadding() );

    setPixRect();
    p.setClipRect( pixRect() );
    p.setClipping( true );

    int pW = pixRect().width();
    int pH = pixRect().height();

    QColor SkyColor( 0, 100, 200 );

    //draw daytime sky if the Sun rises for the current date/location
    if ( SunMaxAlt > -18.0 ) {
        //Display centered on midnight, so need to modulate dawn/dusk by 0.5
        int rise = int( pW * ( 0.5 + SunRise ) );
        int set = int( pW * ( SunSet - 0.5 ) );
        int da = int( pW * ( 0.5 + Dawn ) );
        int du = int( pW * ( Dusk - 0.5 ) );

        if ( SunMinAlt > 0.0 ) {
            // The sun never set and the sky is always blue
            p.fillRect( rect(), SkyColor );
        } else if ( SunMaxAlt < 0.0 && SunMinAlt < -18.0 ) {
            // The sun never rise but the sky is not completely dark
            QLinearGradient grad = QLinearGradient( QPointF( 0.0, 0.0 ), QPointF( du, 0.0 ) );
            grad.setColorAt( 0, SkyColor.darker( SunMaxAlt / -18.0 * 1000 ) );
            grad.setColorAt( 1, Qt::black );
            p.fillRect( QRectF( 0.0, 0.0, du+20.0, pH ), grad );
            
            grad.setStart( QPointF( pW, 0.0 ) );
            grad.setFinalStop( QPointF( da-20.0, 0.0 ) );
            p.fillRect( QRectF( da-20.0, 0.0, pW, pH ), grad );
        } else if ( SunMaxAlt < 0.0 && SunMinAlt > -18.0 ) {
            // The sun never rise but the sky is NEVER completely dark
            QLinearGradient grad = QLinearGradient( QPointF( 0.0, 0.0 ), QPointF( pW, 0.0 ) );
            grad.setColorAt( 0, SkyColor.darker( SunMaxAlt / -18.0 * 1000 ) );
            grad.setColorAt( 0.5, SkyColor.darker( SunMinAlt / -18.0 * 1000 ) );
            grad.setColorAt( 1, SkyColor.darker( SunMaxAlt / -18.0 * 1000 ) );
            p.fillRect( QRectF( 0.0, 0.0, pW, pH ), grad );
        } else if ( Dawn < 0.0 ) {
            // The sun sets and rises but the sky is never completely dark
            p.fillRect( 0, 0, set, int( 0.5 * pH ), SkyColor );
            p.fillRect( rise, 0, pW, int( 0.5 * pH ), SkyColor );

            QLinearGradient grad = QLinearGradient( QPointF( set-20.0, 0.0 ), QPointF( rise, 0.0 ) );
            grad.setColorAt( 0, SkyColor );
            grad.setColorAt( 0.5, SkyColor.darker( SunMinAlt / -18.0 * 1000 ) );
            grad.setColorAt( 1, SkyColor );
            p.fillRect( QRectF( set-20.0, 0.0, rise-set+20.0, pH ), grad );
        } else {
            p.fillRect( 0, 0, set, pH, SkyColor );
            p.fillRect( rise, 0, pW, pH, SkyColor );

            QLinearGradient grad = QLinearGradient( QPointF( set-20.0, 0.0 ), QPointF( du, 0.0 ) );
            grad.setColorAt( 0, SkyColor );
            grad.setColorAt( 1, Qt::black );
            p.fillRect( QRectF( set-20.0, 0.0, du-set+20.0, pH ), grad );

            grad.setStart( QPointF( rise+20.0, 0.0 ) );
            grad.setFinalStop( QPointF( da, 0.0 ) );
            p.fillRect( QRectF( da, 0.0, rise-da+20.0, pH ), grad );
        }
    }

    //draw ground
    p.fillRect( 0, int(0.5*pH), pW, int(0.5*pH), QColor( "#002200" ) );

    foreach( KPlotObject *po, plotObjects() )
    po->draw( &p, this );

    p.setClipping( false );
    drawAxes( &p );

    //Add vertical line indicating "now"
    QTime t = QTime::currentTime();
    double x = 12.0 + t.hour() + t.minute()/60.0 + t.second()/3600.0;
    while ( x > 24.0 ) x -= 24.0;
    int ix = int(x*pW/24.0); //convert to screen pixel coords
    p.setPen( QPen( QBrush("white"), 2.0, Qt::DotLine ) );
    p.drawLine( ix, 0, ix, pH );

    //Label this vertical line with the current time
    p.save();
    QFont smallFont = p.font();
    smallFont.setPointSize( smallFont.pointSize() - 2 );
    p.setFont( smallFont );
    p.translate( ix + 10, pH - 20 );
    p.rotate(-90);
    p.drawText(0, 0, KGlobal::locale()->formatTime( t ) );
    p.restore();

    //Draw crosshairs at clicked position
    if ( MousePoint.x() > 0 ) {
        p.setPen( QPen( QBrush("gold"), 1.0, Qt::SolidLine ) );
        p.drawLine( QLineF( MousePoint.x()+0.5, 0.5, MousePoint.x()+0.5, pixRect().height()-0.5 ) );
        p.drawLine( QLineF( 0.5, MousePoint.y()+0.5, pixRect().width()-0.5, MousePoint.y()+0.5 ) );

        //Label each crosshair line (time and altitude)
        p.setFont( smallFont );
        double a = (pH - MousePoint.y())*180.0/pH - 90.0;
        p.drawText( 20, MousePoint.y() + 10, QString::number(a,'f',2) + QChar(176) );

        double h = MousePoint.x()*24.0/pW - 12.0;
        if ( h < 0.0 ) h += 24.0;
        t = QTime( int(h), int(60.*(h - int(h))) );
        p.save();
        p.translate( MousePoint.x() + 10, pH - 20 );
        p.rotate(-90);
        p.drawText( 0, 0, KGlobal::locale()->formatTime( t ) );
        p.restore();
    }

    p.end();
}