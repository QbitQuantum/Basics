boolean RegisterGameService() {
	DNSServiceErrorType	err = DNSServiceRegister( 
					   &serviceRef, 
					   kDNSServiceFlagsNoAutoRename,		// we want a conflict error
					   InterfaceIndexForName( "en0" ),		// pass 0 for all interfaces
					   "iPhone Doom Classic",
					   serviceName,
					   NULL,	// domain
					   NULL,	// host
					   htons( DOOM_PORT ),
					   0,		// txtLen
					   NULL,	// txtRecord
					   DNSServiceRegisterReplyCallback,
					   NULL		// context
					   );
	
	if ( err != kDNSServiceErr_NoError ) {
		printf( "DNSServiceRegister error\n" );
	} else {
		// block until we get a response, process it, and run the callback
		err = DNSServiceProcessResult( serviceRef );
		if ( err != kDNSServiceErr_NoError ) {
			printf( "DNSServiceProcessResult error\n" );
		}
	}
	return localServer;
}