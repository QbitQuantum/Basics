        QTcpServer* DccCommon::createServerSocketAndListen( QObject* parent, QString* failedReason, int minPort, int maxPort )
        {
            QTcpServer* socket = new QTcpServer( parent );

            if ( minPort > 0 && maxPort >= minPort )  // ports are configured manually
            {
                // set port
                bool found = false;                       // whether succeeded to set port
                for ( int port = minPort; port <= maxPort ; ++port )
                {
                    bool success = socket->listen( QHostAddress::Any, port );
                    if ( ( found = ( success && socket->isListening() ) ) )
                        break;
                    socket->close();
                }
                if ( !found )
                {
                    if ( failedReason )
                        *failedReason = i18n( "No vacant port" );
                    delete socket;
                    return 0;
                }
            }
            else
            {
                // Let the operating system choose a port
                if ( !socket->listen() )
                {
                    if ( failedReason )
                        *failedReason = i18n( "Could not open a socket" );
                    delete socket;
                    return 0;
                }
            }

            return socket;
        }