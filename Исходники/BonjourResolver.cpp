/**
 * \brief main resolve function
 */
ServiceObject	BonjourResolver::do_resolve() {
	debug(LOG_DEBUG, DEBUG_LOG, 0, "start resolving");
	DNSServiceRef	sdRef = NULL;
	DNSServiceResolve(&sdRef, 0, kDNSServiceInterfaceIndexAny,
		_key.name().c_str(), _key.type().c_str(),
		_key.domain().c_str(),
		discover::resolvereply_callback, this);
	int	error;
	do {
		error = DNSServiceProcessResult(sdRef);
	} while (error == kDNSServiceErr_NoError);
	if (sdRef) {
		close(DNSServiceRefSockFD(sdRef));
		DNSServiceRefDeallocate(sdRef);
		sdRef = NULL;
	}
	debug(LOG_DEBUG, DEBUG_LOG, 0, "resolution complete");
	return _object;
}