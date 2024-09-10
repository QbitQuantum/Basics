void KprNetworkInterfaceCleanup()
{
#if TARGET_OS_IPHONE
	if (gNetworkInterfaceReachability) {
		SCNetworkReachabilityUnscheduleFromRunLoop(gNetworkInterfaceReachability, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
		CFRelease(gNetworkInterfaceReachability);
	}
#elif TARGET_OS_MAC
	if (gNetworkInterfaceSource) {
		CFRelease(gNetworkInterfaceSource);
		gNetworkInterfaceSource = NULL;
	}
	if (gNetworkInterfaceStore) {
		CFRelease(gNetworkInterfaceStore);
		gNetworkInterfaceStore = NULL;
	}
#elif TARGET_OS_WIN32
	if (gNetworkInterfaceHandle) {
		CancelMibChangeNotify2(gNetworkInterfaceHandle);
		gNetworkInterfaceHandle = 0;
	}
#elif TARGET_OS_KPL
	#ifdef KPR_CONFIG
	KplNetInterfaceTerminate();
	#endif
#endif
}