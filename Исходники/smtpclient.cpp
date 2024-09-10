void SmtpClient::newConnection()
{
    qMailLog(SMTP) << "newConnection" << flush;
#ifdef USE_ACCOUNTS_QT
    loginFailed = false;
#endif
    if (sending) {
        operationFailed(QMailServiceAction::Status::ErrConnectionInUse, tr("Cannot send message; transport in use"));
        return;
    }

    if (!config.id().isValid()) {
        status = Done;
        operationFailed(QMailServiceAction::Status::ErrConfiguration, tr("Cannot send message without account configuration"));
        return;
    }

    // Load the current configuration for this account
    // Reload the account configuration whenever a new SMTP
    // connection is created, in order to ensure the changes
    // in the account settings are being managed properly.
    config = QMailAccountConfiguration(config.id());

    SmtpConfiguration smtpCfg(config);
    if ( smtpCfg.smtpServer().isEmpty() ) {
        status = Done;
        operationFailed(QMailServiceAction::Status::ErrConfiguration, tr("Cannot send message without SMTP server configuration"));
        return;
    }

    // Calculate the total indicative size of the messages we're sending
    totalSendSize = 0;
    foreach (uint size, sendSize.values())
        totalSendSize += size;

    progressSendSize = 0;
    emit progressChanged(progressSendSize, totalSendSize);

    status = Init;
    sending = true;
    domainName = QByteArray();
    outstandingResponses = 0;

    if (!transport) {
        // Set up the transport
        transport = new QMailTransport("SMTP");

        connect(transport, SIGNAL(readyRead()),
                this, SLOT(readyRead()));
        connect(transport, SIGNAL(connected(QMailTransport::EncryptType)),
                this, SLOT(connected(QMailTransport::EncryptType)));
        connect(transport, SIGNAL(bytesWritten(qint64)),
                this, SLOT(sent(qint64)));
        connect(transport, SIGNAL(updateStatus(QString)),
                this, SIGNAL(updateStatus(QString)));
        connect(transport, SIGNAL(errorOccurred(int,QString)),
                this, SLOT(transportError(int,QString)));
#ifndef QT_NO_OPENSSL
        connect(transport, SIGNAL(sslErrorOccured(QMailServiceAction::Status::ErrorCode,QString)),
                this, SIGNAL(connectionError(QMailServiceAction::Status::ErrorCode,QString)));
#endif
    }