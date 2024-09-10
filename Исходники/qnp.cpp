extern "C" NPError
NPP_SetWindow(NPP instance, NPWindow* window)
{
    if (!qNP) qNP = QNPlugin::create();
    NPError result = NPERR_NO_ERROR;
    _NPInstance* This;

    if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

    This = (_NPInstance*) instance->pdata;


    // take a shortcut if all that was changed is the geometry
    if ( This->widget && window
#ifdef Q_WS_X11
	 && This->window == (Window) window->window
#endif
#ifdef Q_WS_WIN
	 && This->window == (HWND) window->window
#endif
	) {
	This->x = window->x;
	This->y = window->y;
	This->width = window->width;
	This->height = window->height;
	This->widget->resize( This->width, This->height );
	return result;
    }

    delete This->widget;

    if ( !window )
	return result;

#ifdef Q_WS_X11
    This->window = (Window) window->window;
    This->display =
	((NPSetWindowCallbackStruct *)window->ws_info)->display;
#endif
#ifdef Q_WS_WIN
    This->window = (HWND) window->window;
#endif

    This->x = window->x;
    This->y = window->y;
    This->width = window->width;
    This->height = window->height;


    if (!qApp) {
#ifdef Q_WS_X11
	// We are the first Qt-based plugin to arrive
	event_loop = new QNPXt( "qnp", XtDisplayToApplicationContext(This->display) );
	application = new QApplication(This->display);
#endif
#ifdef Q_WS_WIN
	static int argc=0;
	static char **argv={ 0 };
	application = new QApplication( argc, argv );
#ifdef UNICODE
	if ( qWinVersion() & Qt::WV_NT_based )
	    hhook = SetWindowsHookExW( WH_GETMESSAGE, FilterProc, 0, GetCurrentThreadId() );
	else
#endif
	    hhook = SetWindowsHookExA( WH_GETMESSAGE, FilterProc, 0, GetCurrentThreadId() );
#endif
    }

#ifdef Q_WS_X11
    if ( !original_x_errhandler )
    	original_x_errhandler = XSetErrorHandler( dummy_x_errhandler );
#endif

    // New widget on this new window.
    next_pi = This;
    /* This->widget = */ // (happens sooner - in QNPWidget constructor)
    This->instance->newWindow();

    if ( !This->widget )
	return result;

#ifdef Q_WS_X11
    This->widget->resize( This->width, This->height );
    XReparentWindow( This->widget->x11Display(), This->widget->winId(), This->window, 0, 0 );
    XSync( This->widget->x11Display(), False );
#endif
#ifdef Q_WS_WIN
    LONG oldLong = GetWindowLong(This->window, GWL_STYLE);
    ::SetWindowLong(This->window, GWL_STYLE, oldLong | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
    ::SetWindowLong( This->widget->winId(), GWL_STYLE, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
    ::SetParent( This->widget->winId(), This->window );
    This->widget->raise();
    This->widget->setGeometry( 0, 0, This->width, This->height );
#endif
    This->widget->show();
    return result;
}