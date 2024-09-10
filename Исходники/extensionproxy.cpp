void ExtensionProxy::dock(const TQCString& callbackID)
{
    kdDebug(1210) << "Callback ID: " << callbackID << endl;

    _callbackID = callbackID;

    // try to attach to DCOP server
    DCOPClient* dcop = kapp->dcopClient();

    dcop->setNotifications(true);
    connect(dcop, TQT_SIGNAL(applicationRemoved(const TQCString&)),
	    TQT_SLOT(slotApplicationRemoved(const TQCString&)));

    WId win;

    // get docked
    {
	TQCString replyType;
	TQByteArray data, replyData;
	TQDataStream dataStream( data, IO_WriteOnly );

	int actions = 0;
	if(_extension) actions = _extension->actions();
	dataStream << actions;

	int type = 0;
	if (_extension) type = static_cast<int>(_extension->type());
	dataStream << type;

	// we use "call" to know whether it was sucessful

	int screen_number = 0;
	if (tqt_xdisplay())
	    screen_number = DefaultScreen(tqt_xdisplay());
	TQCString appname;
	if (screen_number == 0)
	    appname = "kicker";
	else
	    appname.sprintf("kicker-screen-%d", screen_number);

	if ( !dcop->call(appname, _callbackID, "dockRequest(int,int)",
			 data, replyType, replyData ) )
        {
            kdError() << "Failed to dock into the panel." << endl;
            exit(0);
        }

	TQDataStream reply( replyData, IO_ReadOnly );
	reply >> win;

    }

    if (win) {
        if (_extension)
        {
            _extension->hide();
        }
        QXEmbed::initialize();
        QXEmbed::embedClientIntoWindow( _extension, win );
    }
    else {
        kdError() << "Failed to dock into the panel." << endl;
        if(_extension) delete _extension;
        exit(0);
    }
}