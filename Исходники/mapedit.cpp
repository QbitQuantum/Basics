/* eventFilter is an event filter for misc GUI events. Right now it is used
to dsiplay a popup menu when a user right-clicks on the fill value edit box
*/
bool MapEdit::eventFilter( QObject* object, QEvent* event )
{
	if( (object == fillEdit) && (event->type() == QEvent::MouseButtonPress ) )
	{
		QMouseEvent* mouseEvent = (QMouseEvent*)event;
		if( mouseEvent->button() == Qt::RightButton )
		{
			mouseEvent->accept();
			/*
			QPopupMenu* estimatePopup = new QPopupMenu( this, "estimatePopup" );
			estimatePopup->insertItem( "Estimate Value", fillButton, SLOT( animateClick() ) );

			estimatePopup->exec( mouseEvent->globalPos() );
			delete estimatePopup;
			*/
			return true;
		}
		else
		{
			return QScrollArea::eventFilter( object, event );
		}
	}

	return QScrollArea::eventFilter( object, event );
}