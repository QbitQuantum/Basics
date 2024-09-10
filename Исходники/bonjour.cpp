void QZeroConfPrivate::resolve(void)
{
	DNSServiceErrorType err;

	err = DNSServiceResolve(&resolver, kDNSServiceFlagsTimeout, newService->interface, newService->name.toUtf8(), newService->type.toUtf8(), newService->domain.toUtf8(), (DNSServiceResolveReply) resolverCallback, this);
	if (err == kDNSServiceErr_NoError) {
		int sockfd = DNSServiceRefSockFD(resolver);
		if (sockfd == -1) {
			cleanUp(resolver);
		}
		else {
			resolverSocket = new QSocketNotifier(sockfd, QSocketNotifier::Read, this);
			connect(resolverSocket, SIGNAL(activated(int)), this, SLOT(resolverRead()));
		}
	}