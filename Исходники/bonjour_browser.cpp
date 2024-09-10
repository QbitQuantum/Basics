void BonjourBrowser::browseForServiceType(const QString &service_type) {
    DNSServiceErrorType err = DNSServiceBrowse(&dns_ref_, 0, 0, service_type.toUtf8().constData(),
                              0, bonjourBrowseReply, this);

    if (err != kDNSServiceErr_NoError) {
        emit error(err);
    } else {
        int sock_fd = DNSServiceRefSockFD(dns_ref_);
        if (sock_fd == -1) {
            emit error(kDNSServiceErr_Invalid);
        } else {
            bonjour_socket_ = new QSocketNotifier(sock_fd, QSocketNotifier::Read, this);
            connect(bonjour_socket_, SIGNAL(activated(int)), this, SLOT(bonjourSocketReadyRead()));
        }
    }
}