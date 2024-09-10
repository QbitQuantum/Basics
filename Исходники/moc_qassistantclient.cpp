bool QAssistantClient::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: openAssistant(); break;
    case 1: closeAssistant(); break;
    case 2: showPage((const QString&)static_QUType_QString.get(_o+1)); break;
    case 3: socketConnected(); break;
    case 4: socketConnectionClosed(); break;
    case 5: readPort(); break;
    case 6: socketError((int)static_QUType_int.get(_o+1)); break;
    case 7: readStdError(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}