void MarkerWidget::paintEvent( QPaintEvent * )
{
    buffer.fill( backgroundColor() );

    QTextParagraph *p = ( (Editor*)viewManager->currentView() )->document()->firstParagraph();
    QPainter painter( &buffer );
    int yOffset = ( (Editor*)viewManager->currentView() )->contentsY();
    while ( p ) {
	if ( !p->isVisible() ) {
	    p = p->next();
	    continue;
	}
	if ( p->rect().y() + p->rect().height() - yOffset < 0 ) {
	    p = p->next();
	    continue;
	}
	if ( p->rect().y() - yOffset > height() )
	    break;
	if ( !((p->paragId() + 1) % 10) ) {
	    painter.save();
	    painter.setPen( colorGroup().dark() );
	    painter.drawText( 0, p->rect().y() - yOffset, width() - 20, p->rect().height(),
			      Qt::AlignRight | Qt::AlignTop, QString::number( p->paragId() + 1 ) );
	    painter.restore();
	}
	ParagData *paragData = (ParagData*)p->extraData();
	if ( paragData ) {
	    switch ( paragData->marker ) {
	    case ParagData::Error:
		painter.drawPixmap( 3, p->rect().y() +
				    ( p->rect().height() - errorPixmap->height() ) / 2 -
				    yOffset, *errorPixmap );
		break;
	    case ParagData::Breakpoint:
		painter.drawPixmap( 3, p->rect().y() +
				    ( p->rect().height() - breakpointPixmap->height() ) / 2 -
				    yOffset, *breakpointPixmap );
		break;
	    default:
		break;
	    }
	    switch ( paragData->lineState ) {
	    case ParagData::FunctionStart:
		painter.setPen( colorGroup().foreground() );
		painter.setBrush( colorGroup().base() );
		painter.drawLine( width() - 11, p->rect().y() - yOffset,
				  width() - 11, p->rect().y() + p->rect().height() - yOffset );
		painter.drawRect( width() - 15, p->rect().y() + ( p->rect().height() - 9 ) / 2 - yOffset, 9, 9 );
		painter.drawLine( width() - 13, p->rect().y() + ( p->rect().height() - 9 ) / 2 - yOffset + 4,
				  width() - 9, p->rect().y() +
				  ( p->rect().height() - 9 ) / 2 - yOffset + 4 );
		if ( !paragData->functionOpen )
		    painter.drawLine( width() - 11,
				      p->rect().y() + ( p->rect().height() - 9 ) / 2 - yOffset + 2,
				      width() - 11,
				      p->rect().y() +
				      ( p->rect().height() - 9 ) / 2 - yOffset + 6 );
		break;
	    case ParagData::InFunction:
		painter.setPen( colorGroup().foreground() );
		painter.drawLine( width() - 11, p->rect().y() - yOffset,
				  width() - 11, p->rect().y() + p->rect().height() - yOffset );
		break;
	    case ParagData::FunctionEnd:
		painter.setPen( colorGroup().foreground() );
		painter.drawLine( width() - 11, p->rect().y() - yOffset,
				  width() - 11, p->rect().y() + p->rect().height() - yOffset );
		painter.drawLine( width() - 11, p->rect().y() + p->rect().height() - yOffset,
				  width() - 7, p->rect().y() + p->rect().height() - yOffset );
		break;
	    default:
		break;
	    }
	    if ( paragData->step )
		painter.drawPixmap( 3, p->rect().y() +
				    ( p->rect().height() - stepPixmap->height() ) / 2 -
				    yOffset, *stepPixmap );
	    if ( paragData->stackFrame )
		painter.drawPixmap( 3, p->rect().y() +
				    ( p->rect().height() - stackFrame->height() ) / 2 -
				    yOffset, *stackFrame );
	}
	p = p->next();
    }
    painter.end();

    bitBlt( this, 0, 0, &buffer );
}