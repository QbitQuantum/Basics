void QxtServiceBrowser::browse(/* int iface */)
{
    QStringList subtypes = qxt_d().serviceSubTypes;
    subtypes.prepend(fullServiceType());

    DNSServiceErrorType err;
    err = DNSServiceBrowse(&(qxt_d().service),
                           0,
                           qxt_d().iface,
                           subtypes.join(",_").toUtf8().constData(),
                           domain().isEmpty() ? 0 : domain().toUtf8().constData(),
                           QxtServiceBrowserPrivate::browseServiceCallback,
                           &qxt_d());
    if(err) {
        emit browsingFailed(err);
    } else {
        qxt_d().notifier = new QSocketNotifier(DNSServiceRefSockFD(qxt_d().service), QSocketNotifier::Read, this);
        QObject::connect(qxt_d().notifier, SIGNAL(activated(int)), &qxt_d(), SLOT(socketData()));
    }
}