void BonjourServiceResolver::resolveBonjourRecord(const BonjourRecord &record) {
	ResolveRecord *rr = new ResolveRecord(record, this);

	DNSServiceErrorType err = DNSServiceResolve(& rr->dnssref, 0, 0,
	                          record.serviceName.toUtf8().constData(),
	                          record.registeredType.toUtf8().constData(),
	                          record.replyDomain.toUtf8().constData(),
	                          (DNSServiceResolveReply)bonjourResolveReply, rr);

	if (err == kDNSServiceErr_NoError) {
		int sockfd = DNSServiceRefSockFD(rr->dnssref);
		if (sockfd == -1) {
			err = kDNSServiceErr_Invalid;
		} else {
			rr->bonjourSocket = new QSocketNotifier(sockfd, QSocketNotifier::Read, this);
			connect(rr->bonjourSocket, SIGNAL(activated(int)), this, SLOT(bonjourSocketReadyRead(int)), Qt::QueuedConnection);
			qmResolvers.insert(sockfd, rr);
			return;
		}
	}