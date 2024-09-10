/*!
  Virtual function that draws the mask of the frame's frame.

  If you reimplemented drawFrame(QPainter*) and your widget should
  support transparency you probably have to re-implement this function as well.

  \sa drawFrame(), updateMask(), QWidget::setAutoMask(), QPainter::setClipRect()
*/
void QFrame::drawFrameMask( QPainter* p )
{
    QPoint	p1, p2;
    QRect	r     = frameRect();
    int		type  = fstyle & MShape;
    int		style = fstyle & MShadow;
#ifdef QT_NO_DRAWUTIL
    p->setPen( color1 );
    p->drawRect( r ); //### a bit too simple
#else
    QColorGroup g(color1, color1, color1, color1, color1, color1, color1, color1, color0);

    switch ( type ) {

    case Box:
	if ( style == Plain )
	    qDrawPlainRect( p, r, g.foreground(), lwidth );
	else
	    qDrawShadeRect( p, r, g, style == Sunken, lwidth,
			    midLineWidth() );
	break;

    case Panel:
	if ( style == Plain )
	    qDrawPlainRect( p, r, g.foreground(), lwidth );
	else
	    qDrawShadePanel( p, r, g, style == Sunken, lwidth );
	break;

    case WinPanel:
	if ( style == Plain )
	    qDrawPlainRect( p, r, g.foreground(), wpwidth );
	else
	    qDrawWinPanel( p, r, g, style == Sunken );
	break;

    case HLine:
    case VLine:
	if ( type == HLine ) {
	    p1 = QPoint( r.x(), r.height()/2 );
	    p2 = QPoint( r.x()+r.width(), p1.y() );
	}
	else {
	    p1 = QPoint( r.x()+r.width()/2, 0 );
	    p2 = QPoint( p1.x(), r.height() );
	}
	if ( style == Plain ) {
	    QPen oldPen = p->pen();
	    p->setPen( QPen(g.foreground(),lwidth) );
	    p->drawLine( p1, p2 );
	    p->setPen( oldPen );
	}
	else
	    qDrawShadeLine( p, p1, p2, g, style == Sunken,
			    lwidth, midLineWidth() );
	break;
    }
#endif // QT_NO_DRAWUTIL
}