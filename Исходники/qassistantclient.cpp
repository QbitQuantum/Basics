void QAssistantClient::readPort()
{
    QString p = proc->readLineStdout();
    Q_UINT16 port = p.toUShort();
    if ( port == 0 ) {
	emit error( tr( "Cannot connect to Qt Assistant." ) );
	return;
    }
    socket->connectToHost( host, port );
    disconnect( proc, SIGNAL( readyReadStdout() ),
		this, SLOT( readPort() ) );
}