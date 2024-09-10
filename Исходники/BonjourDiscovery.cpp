BonjourDiscovery::BonjourDiscovery() : ServiceDiscovery() {
	thread = NULL;
	sdRef = NULL;
	DNSServiceErrorType	error = DNSServiceBrowse(&sdRef, 0,
		kDNSServiceInterfaceIndexAny,
		"_astro._tcp", NULL, discover::browsereply_callback, this);
	if (error != kDNSServiceErr_NoError) {
		debug(LOG_ERR, DEBUG_LOG, 0, "browser failed: %d", error);
		throw std::runtime_error("cannot create browser");
	}
	assert(sdRef != NULL);
	debug(LOG_DEBUG, DEBUG_LOG, 0, "DNSServiceBrowse started");
}