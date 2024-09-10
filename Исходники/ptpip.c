static void
_ptpip_enumerate (
	DNSServiceRef sdRef, DNSServiceFlags flags,
	uint32_t interfaceIndex, DNSServiceErrorType errorCode,
	const char *serviceName, const char *regtype, const char *replyDomain,
	void *context
) {
	struct mdnsinfo mdnsi;
	DNSServiceRef		sd;

	if (errorCode != kDNSServiceErr_NoError) {
		gp_log (GP_LOG_ERROR, "ptpip", "Error on _ptp._tcp query.");
		return;
	}
	gp_log (GP_LOG_DEBUG, "ptpip", "found %s, %s, %s", serviceName, regtype, replyDomain);
	mdnsi.list = context;
	mdnsi.name = serviceName;
	DNSServiceResolve (&sd,
		0,
		interfaceIndex,
		serviceName,
		regtype,
		replyDomain,
		_ptpip_resolved,
		&mdnsi
	);
	DNSServiceProcessResult (sd);
	DNSServiceRefDeallocate (sd);
}