void
ITunesScript::transmit( const QString& data )
{
    // thread-safe, basically
    int const port = m_listener->GetPort();

    LOGL( 3, "ITunesScript data being sent " << data << " to port " << port );

    QTcpSocket socket;
    socket.connectToHost( QHostAddress::LocalHost, port );
    if ( socket.waitForConnected( 1000 ) ) //FIXME hangs GUI thread?
    {
        int bytesWritten = socket.write( data.toUtf8() );
        socket.flush();
        socket.waitForDisconnected( 1000 ); //FIXME hangs?

        if ( bytesWritten == -1 )
        {
            LOGL( 1, "Sending submission through socket failed." )
        }
    }