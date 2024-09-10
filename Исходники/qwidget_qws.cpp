void QWidget::setWindowState(uint newstate)
{
    in_show_maximized = 1;
    bool resized = testWFlags( WState_Resized );
    uint oldstate = effectiveState(widget_state);

    widget_state &= ~(WState_Minimized | WState_Maximized | WState_FullScreen);
    if (newstate & WindowMinimized)
	widget_state |= WState_Minimized;
    if (newstate & WindowMaximized)
	widget_state |= WState_Maximized;
    if (newstate & WindowFullScreen)
	widget_state |= WState_FullScreen;

    uint state = effectiveState(widget_state);

    bool needShow = FALSE;
    if (isTopLevel() && state != oldstate) {
	createTLExtra();
	if ( oldstate == 0 ) { //normal
	    topData()->normalGeometry = geometry();
	} else if ( oldstate == WState_FullScreen ) {
	    reparent( 0, topData()->savedFlags, QPoint(0,0) );
	    needShow = isVisible();
	} else if ( oldstate == WState_Minimized ) {
	    needShow = TRUE;
	}

	if ( state == WState_Minimized ) {
	    //### not ideal...
	    hide();
	    needShow = FALSE;
	} else if ( state == WState_FullScreen ) {
	    needShow = needShow || isVisible();
	    topData()->savedFlags = getWFlags();
	    reparent( 0, WType_TopLevel | WStyle_Customize | WStyle_NoBorder |
		      // preserve some widget flags
		      (getWFlags() & 0xffff0000),
		      QPoint( 0, 0));
	    const QRect screen = qApp->desktop()->screenGeometry( qApp->desktop()->screenNumber( this ) );
	    move( screen.topLeft() );
	    resize( screen.size() );
	    if ( !resized )
		clearWState( WState_Resized );
	    raise();
	} else if ( state == WState_Maximized ) {
#ifndef QT_NO_QWS_MANAGER
	    if ( extra && extra->topextra && extra->topextra->qwsManager )
		extra->topextra->qwsManager->maximize();
	    else
#endif
		setGeometry( qt_maxWindowRect );
	    if ( !resized )
		clearWState( WState_Resized );
	} else { //normal
	    QRect r = topData()->normalGeometry;
	    if ( r.width() >= 0 ) {
		topData()->normalGeometry = QRect(0,0,-1,-1);
		setGeometry( r );
	    }
	}
    }

    in_show_maximized = 0;

    if (needShow)
	show();

    if (newstate & WindowActive)
	setActiveWindow();

    QEvent e(QEvent::WindowStateChange);
    QApplication::sendEvent(this, &e);
}