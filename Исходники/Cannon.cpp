void CannonField::paintEvent( QPaintEvent *e )
{
    QRect updateR = e->rect();
    QPainter p( this );

    if ( gameEnded ) {
	p.setPen( black );
	p.setFont( QFont( "Courier", 48, QFont::Bold ) );
	p.drawText( rect(), AlignCenter, "Game Over" );
    }
    if ( updateR.intersects( cannonRect() ) )
	paintCannon( &p );
    if ( isShooting() && updateR.intersects( shotRect() ) )
	paintShot( &p );
    if ( !gameEnded && updateR.intersects( targetRect() ) )
	paintTarget( &p );
}