/*!\reimp
 */
void QWindowsStyle::drawScrollBarControls( QPainter* p, const QScrollBar* sb, int sliderStart, uint controls, uint activeControl )
{
#ifndef QT_NO_SCROLLBAR
#define ADD_LINE_ACTIVE ( activeControl == AddLine )
#define SUB_LINE_ACTIVE ( activeControl == SubLine )
    QColorGroup g  = sb->colorGroup();

    int sliderMin, sliderMax, sliderLength, buttonDim;
    scrollBarMetrics( sb, sliderMin, sliderMax, sliderLength, buttonDim );

    if (sliderStart > sliderMax) { // sanity check
	sliderStart = sliderMax;
    }

    int b = 0;
    int dimB = buttonDim;
    QRect addB;
    QRect subB;
    QRect addPageR;
    QRect subPageR;
    QRect sliderR;
    int addX, addY, subX, subY;
    int length = HORIZONTAL ? sb->width()  : sb->height();
    int extent = HORIZONTAL ? sb->height() : sb->width();

    if ( HORIZONTAL ) {
	subY = addY = ( extent - dimB ) / 2;
	subX = b;
	addX = length - dimB - b;
    } else {
	subX = addX = ( extent - dimB ) / 2;
	subY = b;
	addY = length - dimB - b;
    }

    subB.setRect( subX,subY,dimB,dimB );
    addB.setRect( addX,addY,dimB,dimB );

    int sliderEnd = sliderStart + sliderLength;
    int sliderW = extent - b*2;
    if ( HORIZONTAL ) {
	subPageR.setRect( subB.right() + 1, b,
			  sliderStart - subB.right() - 1 , sliderW );
	addPageR.setRect( sliderEnd, b, addX - sliderEnd, sliderW );
	sliderR .setRect( sliderStart, b, sliderLength, sliderW );
    } else {
	subPageR.setRect( b, subB.bottom() + 1, sliderW,
			  sliderStart - subB.bottom() - 1 );
	addPageR.setRect( b, sliderEnd, sliderW, addY - sliderEnd );
	sliderR .setRect( b, sliderStart, sliderW, sliderLength );
    }

    bool maxedOut = (sb->maxValue() == sb->minValue());
    if ( controls & AddLine ) {
	qDrawWinPanel( p, addB.x(), addB.y(),
		       addB.width(), addB.height(), g,
		       ADD_LINE_ACTIVE, &g.brush( QColorGroup::Button ) );
	drawArrow( p, VERTICAL ? DownArrow : RightArrow,
		   ADD_LINE_ACTIVE, addB.x()+2, addB.y()+2,
		   addB.width()-4, addB.height()-4, g, !maxedOut );
    }
    if ( controls & SubLine ) {
	qDrawWinPanel( p, subB.x(), subB.y(),
		       subB.width(), subB.height(), g,
		       SUB_LINE_ACTIVE, &g.brush( QColorGroup::Button )  );
	drawArrow( p, VERTICAL ? UpArrow : LeftArrow,
		   SUB_LINE_ACTIVE, subB.x()+2, subB.y()+2,
		   subB.width()-4, subB.height()-4, g, !maxedOut );
    }
    QBrush br =
	g.brush( QColorGroup::Light ).pixmap() ?
		 g.brush( QColorGroup::Light )     :
		 QBrush(g.light(), Dense4Pattern);
    p->setBrush( br );
    p->setPen( NoPen );
    p->setBackgroundMode( OpaqueMode );
    if ( maxedOut ) {
	p->drawRect( sliderR );
    } else {
	if ( (controls & SubPage && SubPage == activeControl) ||
	     (controls  & AddPage && AddPage == activeControl) ) {
	    QBrush b = p->brush();
	    QColor c = p->backgroundColor();
// 	    p->fillRect( AddPage == activeControl? addPageR : subPageR, g.fillDark() );
	    p->setBackgroundColor( g.dark() );
	    p->setBrush( QBrush(g.shadow(), Dense4Pattern) );
	    p->drawRect( AddPage == activeControl? addPageR : subPageR );
	    p->setBackgroundColor( c );
	    p->setBrush( b );
	}
	if ( controls & SubPage && SubPage != activeControl)
	    p->drawRect( subPageR );
	if ( controls & AddPage && AddPage != activeControl)
	    p->drawRect( addPageR );
	if ( controls & Slider ) {
	    if ( !maxedOut ) {
		QPoint bo = p->brushOrigin();
		if ( !sb->testWState(WState_GlobalBrushOrigin) )
		    p->setBrushOrigin(sliderR.topLeft());
		qDrawWinPanel( p, sliderR.x(), sliderR.y(),
				 sliderR.width(), sliderR.height(), g,
				 FALSE, &g.brush( QColorGroup::Button ) );
		p->setBrushOrigin(bo);
	    }
	}
    }
    // ### perhaps this should not be able to accept focus if maxedOut?
    if ( sb->hasFocus() && (controls & Slider) )
	drawFocusRect(p, QRect(sliderR.x()+2, sliderR.y()+2,
			       sliderR.width()-5, sliderR.height()-5), g,
		      &sb->backgroundColor());
#endif
}