void PhotoView::mouseMoveEvent ( QMouseEvent * event )
{
    // logDebug() << endl;
    _idleTimer.start( _idleTimeout );
    showCursor();

    QGraphicsView::mouseMoveEvent( event );
}