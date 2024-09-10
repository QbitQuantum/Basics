//
// Setup the EventFilter
//
void FaceApp::SetupEventFilter( FaceTrackNoIR *window ) {

	mainWindow = window;
	msgID_FTClient = RegisterWindowMessageA ( FT_PROGRAMID );
	qDebug() << "FaceApp::SetupEventFilter says: Message ID =" << msgID_FTClient;
	msgID_FTIR_Register = RegisterWindowMessageA ( FTIR_REGISTER_PROGRAMHANDLE );
	msgID_FTIR_UnRegister = RegisterWindowMessageA ( FTIR_UNREGISTER_PROGRAMHANDLE );

	////if ( RegisterHotKey( window->winId(), 777, MOD_WIN, VK_HOME ) ) {
	////	qDebug() << "FaceApp::SetupEventFilter says: RegisterHotKey HOME =" << VK_HOME;
	////}
	////if ( RegisterHotKey( window->winId(), 778, MOD_WIN, VK_END ) ) {
	////	qDebug() << "FaceApp::SetupEventFilter says: RegisterHotKey END =" << VK_END;
	////}
	////
	////QAbstractEventDispatcher *evtdis = QAbstractEventDispatcher::instance();
	////if (evtdis != NULL) {
	////	qDebug() << "FaceApp::SetupEventFilter says: EventDispatcher found!";
	////}

}