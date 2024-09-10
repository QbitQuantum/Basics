void QWinWidget::init() 
{
    Q_ASSERT(hParent);

    if (hParent) {
	// make the widget window style be WS_CHILD so SetParent will work
	QT_WA({
	    SetWindowLong(winId(), GWL_STYLE, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	}, {
	    SetWindowLongA(winId(), GWL_STYLE, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	})