OSStatus	ExplorerBarWindow::StartResolve( ServiceInfo *inService )
{
	OSStatus		err;
	
	check( inService );
	
	// Stop any current resolve that may be in progress.
	
	StopResolve();
	
	// Resolve the service.
	err = DNSServiceResolve( &mResolveServiceRef, 0, 0, 
		inService->name, inService->type, inService->domain, (DNSServiceResolveReply) ResolveCallBack, inService->handler );
	require_noerr( err, exit );

	err = WSAAsyncSelect((SOCKET) DNSServiceRefSockFD(mResolveServiceRef), m_hWnd, WM_PRIVATE_SERVICE_EVENT, FD_READ|FD_CLOSE);
	require_noerr( err, exit );
	
	m_serviceRefs.push_back(mResolveServiceRef);

exit:
	return( err );
}