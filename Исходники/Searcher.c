// When a new named instance of a service is found, FoundInstance() is called.
// In this sample code we turn around and immediately to a DNSServiceResolve() to resolve that service name
// to find its target host, port, and txtinfo, but a normal browing application would just display the name.
// Resolving every single thing you find can be quite hard on the network, so you shouldn't do this
// in a real application. Defer resolving until the client has picked which instance from the
// long list of services is the one they want to use, and then resolve only that one.
static void FoundInstance(DNSServiceRef client, DNSServiceFlags flags, uint32_t interface, DNSServiceErrorType errorCode,
    const char *replyName, const char *replyType, const char *replyDomain, void *context)
	{
#pragma unused(client, interface, errorCode)
	SearcherServices *services = (SearcherServices *)context;
	linkedServiceInfo *info;

	if (!services) { DebugStr("\pFoundInstance: services is NULL"); return; }
	
	info = (linkedServiceInfo *)OTAllocMem(sizeof(linkedServiceInfo));
	if (!info) { services->lostRecords = true; return; }
	
	info->services = services;
	strcpy(info->name, replyName);
	strcpy(info->type, replyType);
	strcpy(info->domn, replyDomain);
	info->text[0] = 0;
	info->add = (flags & kDNSServiceFlagsAdd) ? true : false;
	info->dom = false;
	
	if (!info->add)	// If TTL == 0 we're deleting a service,
		OTLIFOEnqueue(&services->serviceinfolist, &info->link);
	else								// else we're adding a new service
		DNSServiceResolve(&info->sdRef, 0, 0, info->name, info->type, info->domn, FoundInstanceInfo, info);
	}