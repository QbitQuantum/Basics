/*
 * Handle newly-discovered services
 */
static void
browser_callback(
	__unused DNSServiceRef sdRef,
	DNSServiceFlags servFlags,
	uint32_t interfaceIndex,
	DNSServiceErrorType errorCode,
	const char *serviceName,
	const char *regType,
	const char *replyDomain,
	__unused void *context)
{
	DNSServiceErrorType err;
	CFSocketContext ctx = { 0, NULL, NULL, NULL, NULL };
	struct cbinfo *info;

        if (errorCode != kDNSServiceErr_NoError) {
		printf("DNS service discovery error: %d\n", errorCode);
		return;
	}
#ifdef DEBUG
	printf("browse: %s: %s, %s, %s\n",
		(servFlags & kDNSServiceFlagsAdd) ? "new" : "gone",
		serviceName, regType, replyDomain);
#endif
	if (!(servFlags & kDNSServiceFlagsAdd))
		return;

	info = malloc(sizeof(*info));
	if (!info) {
		printf("browse: out of memeory\n");
		return;
	}

	err = DNSServiceResolve(&info->sdref, servFlags, interfaceIndex, serviceName, regType, replyDomain, resolve_callback, info);
	if (err != kDNSServiceErr_NoError) {
		printf("DNSServiceResolve failed: %d\n", err);
		free(info);
		return;
	}
	ctx.info = (void*)info;
	info->sockref = CFSocketCreateWithNative(kCFAllocatorDefault, DNSServiceRefSockFD(info->sdref),
				kCFSocketReadCallBack, socket_callback, &ctx);
	if (!info->sockref) {
		printf("CFSocketCreateWithNative failed\n");
		DNSServiceRefDeallocate(info->sdref);
		free(info);
		return;
	}
	info->rls = CFSocketCreateRunLoopSource(kCFAllocatorDefault, info->sockref, 1);
	CFRunLoopAddSource(CFRunLoopGetCurrent(), info->rls, kCFRunLoopDefaultMode);
}