/* extern */ Boolean
_CFServerStart(_CFServerRef server, CFStringRef name, CFStringRef type, UInt32 port) {
	
	Server* s = (Server*)server;

	CFDataRef address = NULL;
	
	do {
        unsigned i;
		CFRunLoopRef rl = CFRunLoopGetCurrent();
        CFAllocatorRef alloc = CFGetAllocator(server);
		
        struct sockaddr_in addr4;
        struct sockaddr_in6 addr6;
				
		// Make sure the port is valid (0 - 65535).
		if ((port & 0xFFFF0000U) != 0)
			break;
		
		// NULL means to use the machine name.
		if (name == NULL)
			name = _kCFServerEmptyString;
		
		for (i = 0; i < (sizeof(s->_sockets) / sizeof(s->_sockets[0])); i++) {
		
			// Create the run loop source for putting on the run loop.
			CFRunLoopSourceRef src = CFSocketCreateRunLoopSource(alloc, s->_sockets[i], 0);
			if (src == NULL)
				break;
				
			// Add the run loop source to the current run loop and default mode.
			CFRunLoopAddSource(rl, src, kCFRunLoopCommonModes);
			CFRelease(src);
		}

		memset(&addr4, 0, sizeof(addr4));
		
		// Put the local port and address into the native address.
#if !defined(__WIN32__)
        addr4.sin_len = sizeof(addr4);
#endif
		addr4.sin_family = AF_INET;
		addr4.sin_port = htons((UInt16)port);
		addr4.sin_addr.s_addr = htonl(INADDR_ANY);
		
		// Wrap the native address structure for CFSocketCreate.
		address = CFDataCreateWithBytesNoCopy(alloc, (const UInt8*)&addr4, sizeof(addr4), kCFAllocatorNull);
		
		// If it failed to create the address data, bail.
		if (address == NULL)
			break;
			
		// Set the local binding which causes the socket to start listening.
		if (CFSocketSetAddress(s->_sockets[0], address) != kCFSocketSuccess)
			break;
		
		CFRelease(address);
		
		address = CFSocketCopyAddress(s->_sockets[0]);
		memcpy(&addr4, CFDataGetBytePtr(address), CFDataGetLength(address));
            
		port = ntohs(addr4.sin_port);

		CFRelease(address);

		memset(&addr6, 0, sizeof(addr6));

        // Put the local port and address into the native address.
        addr6.sin6_family = AF_INET6;
#ifndef __WIN32__
        addr6.sin6_port = htons((UInt16)port);
        addr6.sin6_len = sizeof(addr6);
        memcpy(&(addr6.sin6_addr), &in6addr_any, sizeof(addr6.sin6_addr));
#else
#ifndef __MINGW32__
        // real MS headers have this
        IN6ADDR_SETANY(addr6);
        addr6.sin6_port = htons((UInt16)port);
#else
        addr6.sin6_port = htons((UInt16)port);
        // mingw's w32 headers have this INIT macro instead, for some odd reason
        struct sockaddr_in6 in6addr_any = IN6ADDR_ANY_INIT;
        memcpy(&(addr6.sin6_addr), &in6addr_any, sizeof(addr6.sin6_addr));
#endif
#endif
        
		// Wrap the native address structure for CFSocketCreate.
		address = CFDataCreateWithBytesNoCopy(alloc, (const UInt8*)&addr6, sizeof(addr6), kCFAllocatorNull);
			
		// Set the local binding which causes the socket to start listening.
		if (CFSocketSetAddress(s->_sockets[1], address) != kCFSocketSuccess)
			break;
		
		// Save the name, service type and port.
        s->_name = CFRetain(name);
		s->_type = type ? CFRetain(type) : NULL;
		s->_port = port;

#if defined(__MACH__)
        // Attempt to register the service on the network. 
		if (type && !_ServerCreateAndRegisterNetService(s))
            break;
#endif

        // Release this since it's not needed any longer. 
		CFRelease(address);
	
		return TRUE;
        
	} while (0);
	
	// Handle the error cleanup.
	
	// Release the address data if it was created.
	if (address)
		CFRelease(address);

	// Kill the socket if it was created.
	_ServerReleaseSocket(s);

	return FALSE;
}