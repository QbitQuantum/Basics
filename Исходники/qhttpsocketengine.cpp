void QHttpSocketEngine::slotSocketReadNotification()
{
    Q_D(QHttpSocketEngine);
    if (d->state != Connected && d->socket->bytesAvailable() == 0)
        return;

    if (d->state == Connected) {
        // Forward as a read notification.
        if (d->readNotificationEnabled)
            emitReadNotification();
        return;
    }

    if (d->state == ConnectSent) {
        d->reply->d_func()->state = QHttpNetworkReplyPrivate::NothingDoneState;
        d->state = ReadResponseHeader;
    }

    if (d->state == ReadResponseHeader) {
        bool ok = readHttpHeader();
        if (!ok) {
            // protocol error, this isn't HTTP
            d->socket->close();
            setState(QAbstractSocket::UnconnectedState);
            setError(QAbstractSocket::ProxyProtocolError, tr("Did not receive HTTP response from proxy"));
            emitConnectionNotification();
            return;
        }
        if (d->state == ReadResponseHeader)
            return; // readHttpHeader() was not done yet, need to wait for more header data
    }

    if (d->state == ReadResponseContent) {
        char dummybuffer[4096];
        while (d->pendingResponseData) {
            int read = d->socket->read(dummybuffer, qMin(sizeof(dummybuffer), (size_t)d->pendingResponseData));
            if (read == 0)
                return;
            if (read == -1) {
                d->socket->disconnectFromHost();
                emitWriteNotification();
                return;
            }
            d->pendingResponseData -= read;
        }
        if (d->pendingResponseData > 0)
            return;
        if (d->reply->d_func()->statusCode == 407)
            d->state = SendAuthentication;
    }

    int statusCode = d->reply->statusCode();
    QAuthenticatorPrivate *priv = 0;
    if (statusCode == 200) {
        d->state = Connected;
        setLocalAddress(d->socket->localAddress());
        setLocalPort(d->socket->localPort());
        setState(QAbstractSocket::ConnectedState);
        d->authenticator.detach();
        priv = QAuthenticatorPrivate::getPrivate(d->authenticator);
        priv->hasFailed = false;
    } else if (statusCode == 407) {
        if (d->authenticator.isNull())
            d->authenticator.detach();
        priv = QAuthenticatorPrivate::getPrivate(d->authenticator);

        if (d->credentialsSent && priv->phase != QAuthenticatorPrivate::Phase2) {
            // Remember that (e.g.) NTLM is two-phase, so only reset when the authentication is not currently in progress.
            //407 response again means the provided username/password were invalid.
            d->authenticator = QAuthenticator(); //this is needed otherwise parseHttpResponse won't set the state, and then signal isn't emitted.
            d->authenticator.detach();
            priv = QAuthenticatorPrivate::getPrivate(d->authenticator);
            priv->hasFailed = true;
        }

        priv->parseHttpResponse(d->reply->header(), true);

        if (priv->phase == QAuthenticatorPrivate::Invalid) {
            // problem parsing the reply
            d->socket->close();
            setState(QAbstractSocket::UnconnectedState);
            setError(QAbstractSocket::ProxyProtocolError, tr("Error parsing authentication request from proxy"));
            emitConnectionNotification();
            return;
        }

        bool willClose;
        QByteArray proxyConnectionHeader = d->reply->headerField("Proxy-Connection");
        // Although most proxies use the unofficial Proxy-Connection header, the Connection header
        // from http spec is also allowed.
        if (proxyConnectionHeader.isEmpty())
            proxyConnectionHeader = d->reply->headerField("Connection");
        proxyConnectionHeader = proxyConnectionHeader.toLower();
        if (proxyConnectionHeader == "close") {
            willClose = true;
        } else if (proxyConnectionHeader == "keep-alive") {
            willClose = false;
        } else {
            // no Proxy-Connection header, so use the default
            // HTTP 1.1's default behaviour is to keep persistent connections
            // HTTP 1.0 or earlier, so we expect the server to close
            willClose = (d->reply->majorVersion() * 0x100 + d->reply->minorVersion()) <= 0x0100;
        }

        if (willClose) {
            // the server will disconnect, so let's avoid receiving an error
            // especially since the signal below may trigger a new event loop
            d->socket->disconnectFromHost();
            d->socket->readAll();
            //We're done with the reply and need to reset it for the next connection
            delete d->reply;
            d->reply = new QHttpNetworkReply;
        }

        if (priv->phase == QAuthenticatorPrivate::Done)
            emit proxyAuthenticationRequired(d->proxy, &d->authenticator);
        // priv->phase will get reset to QAuthenticatorPrivate::Start if the authenticator got modified in the signal above.
        if (priv->phase == QAuthenticatorPrivate::Done) {
            setError(QAbstractSocket::ProxyAuthenticationRequiredError, tr("Authentication required"));
            d->socket->disconnectFromHost();
        } else {
            // close the connection if it isn't already and reconnect using the chosen authentication method
            d->state = SendAuthentication;
            if (willClose) {
                d->socket->connectToHost(d->proxy.hostName(), d->proxy.port());
            } else {
                // send the HTTP CONNECT again
                slotSocketConnected();
            }
            return;
        }
    } else {
        d->socket->close();
        setState(QAbstractSocket::UnconnectedState);
        if (statusCode == 403 || statusCode == 405) {
            // 403 Forbidden
            // 405 Method Not Allowed
            setError(QAbstractSocket::SocketAccessError, tr("Proxy denied connection"));
        } else if (statusCode == 404) {
            // 404 Not Found: host lookup error
            setError(QAbstractSocket::HostNotFoundError, QAbstractSocket::tr("Host not found"));
        } else if (statusCode == 503) {
            // 503 Service Unavailable: Connection Refused
            setError(QAbstractSocket::ConnectionRefusedError, QAbstractSocket::tr("Connection refused"));
        } else {
            // Some other reply
            //qWarning("UNEXPECTED RESPONSE: [%s]", responseHeader.toString().toLatin1().data());
            setError(QAbstractSocket::ProxyProtocolError, tr("Error communicating with HTTP proxy"));
        }
    }

    // The handshake is done; notify that we're connected (or failed to connect)
    emitConnectionNotification();
}