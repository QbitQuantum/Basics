/*****************************************************************************
 * NetBrowserInfoCreate
 * - 
 * The method creates a NetBrowserInfo Object and initalizes it.
 *****************************************************************************/
NetBrowserInfo* NetBrowserInfoCreate(CFStringRef serviceType, CFStringRef domain, void* context)
{
	NetBrowserInfo* outObj = NULL;
	DNSServiceRef browserRef = NULL;
	char* cServiceType = NULL;
	char* cDomain = NULL;
	Boolean success = true;
	
	CFIndex serviceSize = CFStringGetMaximumSizeForEncoding(CFStringGetLength(serviceType), kCFStringEncodingUTF8);
	cServiceType = calloc(serviceSize, 1);
	success = CFStringGetCString(serviceType, cServiceType, serviceSize, kCFStringEncodingUTF8);
	
	if (domain)
	{
		CFIndex domainSize = CFStringGetMaximumSizeForEncoding(CFStringGetLength(domain), kCFStringEncodingUTF8);
		cDomain = calloc(serviceSize, 1);
		success = success && CFStringGetCString(domain, cDomain, domainSize, kCFStringEncodingUTF8);
	}
	
	if (!success)
	{
		fprintf(stderr, "LaunchEvent has badly encoded service type or domain.\n");
		free(cServiceType);

		if (cDomain)
			free(cDomain);
		
		return NULL;
	}
	
	DNSServiceErrorType err = DNSServiceBrowse(&browserRef, 0, 0, cServiceType, cDomain, ServiceBrowserCallback, context);

	if (err != kDNSServiceErr_NoError)
	{
		fprintf(stderr, "Failed to create browser for %s, %s\n", cServiceType, cDomain);
		free(cServiceType);
		
		if (cDomain)
			free(cDomain);
		
		return NULL;
	}

	DNSServiceSetDispatchQueue(browserRef, dispatch_get_main_queue());
	
	
	outObj = malloc(sizeof(NetBrowserInfo));
	
	outObj->refCount = 1;
	outObj->browserRef = browserRef;

	free(cServiceType);
								  
	if (cDomain)
		free(cDomain);
	
	return outObj;
}