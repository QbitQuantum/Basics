bool QDesignerToolBar::eventFilter( QObject *o, QEvent *e )
{
    if ( !o || !e || o->inherits( "QDockWindowHandle" ) || o->inherits( "QDockWindowTitleBar" ) )
	return QToolBar::eventFilter( o, e );

    if ( o == this && e->type() == QEvent::MouseButtonPress &&
	 ( ( QMouseEvent*)e )->button() == LeftButton ) {
	mousePressEvent( (QMouseEvent*)e );
	return TRUE;
    }

    if ( o == this )
	return QToolBar::eventFilter( o, e );

    if ( e->type() == QEvent::MouseButtonPress ) {
	QMouseEvent *ke = (QMouseEvent*)e;
	fixObject( o );
	if ( !o )
	    return FALSE;
	buttonMousePressEvent( ke, o );
	return TRUE;
    } else if(e->type() == QEvent::ContextMenu ) {
	QContextMenuEvent *ce = (QContextMenuEvent*)e;
	fixObject( o );
	if( !o )
	    return FALSE;
	buttonContextMenuEvent( ce, o );
	return TRUE;
    } else if ( e->type() == QEvent::MouseMove ) {
	QMouseEvent *ke = (QMouseEvent*)e;
	fixObject( o );
	if ( !o )
	    return FALSE;
	buttonMouseMoveEvent( ke, o );
	return TRUE;
    } else if ( e->type() == QEvent::MouseButtonRelease ) {
	QMouseEvent *ke = (QMouseEvent*)e;
	fixObject( o );
	if ( !o )
	    return FALSE;
	buttonMouseReleaseEvent( ke, o );
	return TRUE;
    } else if ( e->type() == QEvent::DragEnter ) {
	QDragEnterEvent *de = (QDragEnterEvent*)e;
	if ( de->provides( "application/x-designer-actions" ) ||
	     de->provides( "application/x-designer-actiongroup" ) ||
	     de->provides( "application/x-designer-separator" ) )
	    de->accept();
    } else if ( e->type() == QEvent::DragMove ) {
	QDragMoveEvent *de = (QDragMoveEvent*)e;
	if ( de->provides( "application/x-designer-actions" ) ||
	     de->provides( "application/x-designer-actiongroup" ) ||
	     de->provides( "application/x-designer-separator" ) )
	    de->accept();
    }

    return QToolBar::eventFilter( o, e );
}