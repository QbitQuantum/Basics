/*!
 * Attempts to register the service on the local network.
 *
 * If noAutoRename is set to true, registration will fail if another service of the same service type
 * is already registered with the same service name. Otherwise, the service name will be updated with
 * a number to make it unique.
 *
 * \sa registered
 * \sa registrationError
 */
void QxtDiscoverableService::registerService(bool noAutoRename)
{
    if(state() != Unknown) {
        qWarning() << "QxtDiscoverableService: Cannot register service while not in Unknown state";
        emit registrationError(0);
        return;
    }

    QStringList subtypes = qxt_d().serviceSubTypes;
    subtypes.prepend(fullServiceType());

    DNSServiceErrorType err;
    err = DNSServiceRegister(&(qxt_d().service),
                             noAutoRename ? kDNSServiceFlagsNoAutoRename : 0,
                             qxt_d().iface,
                             serviceName().isEmpty() ? 0 : serviceName().toUtf8().constData(),
                             subtypes.join(",_").toUtf8().constData(),
                             domain().isEmpty() ? 0 : domain().toUtf8().constData(),
                             host().isEmpty() ? 0 : host().toUtf8().constData(),
                             qxt_d().port,
                             1, // must include null terminator
                             "",
                             QxtDiscoverableServicePrivate::registerServiceCallback,
                             &qxt_d());
    if(err != kDNSServiceErr_NoError) {
        qxt_d().state = Unknown;
        emit registrationError(err);
    } else {
        qxt_d().state = Registering;
        qxt_d().notifier = new QSocketNotifier(DNSServiceRefSockFD(qxt_d().service), QSocketNotifier::Read, this);
        QObject::connect(qxt_d().notifier, SIGNAL(activated(int)), &qxt_d(), SLOT(socketData()));
    }
}