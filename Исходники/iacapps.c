static pascal OSErr CoercePSNToType (DescType typecode, Ptr dataptr, Size datasize, DescType totype, long refcon, AEDesc *result) {
	
	#pragma unused (typecode, datasize, totype, refcon)
	
	ProcessInfoRec info;
	OSErr ec;
	
	info.processInfoLength = (long) sizeof (info);
	
	info.processName = nil;
	
	info.processAppSpec = nil;
	
	//Code check by Timothy Paustian Tuesday, April 25, 2000 10:22:33 PM
	//somewhat of a dangerous call, This routine assumed the dataptr coming in
	//is a ProcessSerialNumber, only accesses the signature so OK.
	ec = GetProcessInformation ((ProcessSerialNumber *) dataptr, &info);
	
	if (ec != noErr)
		return (ec);
		
	(*result).descriptorType = typeType;
	
	#if TARGET_API_MAC_CARBON == 1 /*PBS 03/14/02: AE OS X fix.*/
	
		return (putdescdatapointer (result, typeType, &info.processSignature, 4));
	
	#else
	
		return (PtrToHand (&info.processSignature, &(*result).dataHandle, 4));
	
	#endif
	} /*CoercePSNToType*/