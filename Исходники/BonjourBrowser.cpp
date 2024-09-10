void BonjourBrowser::browseForServiceType (const QString& serviceType)
{
    DNSServiceErrorType err;
    err = DNSServiceBrowse(&d->dnssref, 0, 0,
                           serviceType.toUtf8().constData(), 0,
                           bonjourBrowseReply, this);
    if (err != kDNSServiceErr_NoError) {
        setError(err);
    } else {
        int sockfd = DNSServiceRefSockFD(d->dnssref);
        if (sockfd == -1) {
            setError(kDNSServiceErr_Invalid);
        } else {
            d->bonjourSocket = new QSocketNotifier(
                sockfd, QSocketNotifier::Read, this);
            connect(d->bonjourSocket, SIGNAL(activated(int)),
                    SLOT(bonjourSocketReadyRead()));
        }
    }
}