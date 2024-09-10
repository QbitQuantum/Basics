bool QLineEdit::event( QEvent * e )
{
#if 0 // it works, but we'll wait with enabling it.
    if ( !e )
	return QWidget::event( e );

    if ( e->type() == Event_DragEnter ) {
	if ( ((QDragEnterEvent *) e)->provides( "text/plain" ) ) {
	    ((QDragEnterEvent *) e)->accept( rect() );
	    return TRUE;
	}
    } else if ( e->type() == Event_DragLeave ) {
	return TRUE;
    } else if ( e->type() == Event_Drop ) {
	QDropEvent * de = (QDropEvent *) e;
	QString str;
	if ( QTextDrag::decode( de, str ) ) {
	    if ( !hasMarkedText() ) {
		int margin = frame() ? 2 : 0;
		setCursorPosition( xPosToCursorPos( &tbuf[(int)offset],
						    fontMetrics(),
						    de->pos().x() - margin,
						    width() - 2*margin ) );
	    }
	    insert( str );
	    de->accept();
	} else {
	    de->ignore();
	}
	return TRUE;
    }
#endif
    return QWidget::event( e );
}