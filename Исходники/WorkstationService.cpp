DNSServiceErrorType
RegisterWorkstationService(MyDNSServiceState *ref, CFStringRef serviceName)
{
	char name[64];
	DNSServiceErrorType error = kDNSServiceErr_BadParam;
	
	if (CFStringGetCString(serviceName, name, sizeof(name), kCFStringEncodingUTF8)) {

		uuid_t compUUID;
		CFDataRef cfTXTRecord = NULL;
		struct timespec waitTime = { 0 };
		
		if ( gethostuuid(compUUID, &waitTime) == 0 )
		{
			CFMutableDictionaryRef txtRecordDict = CFDictionaryCreateMutable( kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks,
																			  &kCFTypeDictionaryValueCallBacks );
			uuid_string_t uuidstr;
			
			uuid_unparse_upper( compUUID, uuidstr );
			CFStringRef cfUUID = CFStringCreateWithCString( kCFAllocatorDefault, uuidstr, kCFStringEncodingUTF8 );
			CFDictionarySetValue( txtRecordDict, CFSTR("uuid"), cfUUID );
			DbgLog( kLogInfo, "Workstation service - uuid = %s", uuidstr );
			DSCFRelease( cfUUID );
			
			cfTXTRecord = CFNetServiceCreateTXTDataWithDictionary( kCFAllocatorDefault, txtRecordDict );
			
			DSCFRelease( txtRecordDict );
		}
		else
		{
			DbgLog( kLogError, "Failed to get host UUID from gethostuuid()" );
		}
		
		error = DNSServiceRegister(&ref->service,
								   kDNSServiceFlagsNoAutoRename,
								   kDNSServiceInterfaceIndexAny,
								   name,
								   kWorkstationType,
								   NULL,
								   NULL,
								   htons(kWorkstationPort),
								   (cfTXTRecord ? CFDataGetLength(cfTXTRecord) : 0),
								   (cfTXTRecord ? CFDataGetBytePtr(cfTXTRecord) : NULL),
								   RegisterWorkstationCallBack,
								   (void *)ref);
		
		DSCFRelease( cfTXTRecord );
	}

    if (kDNSServiceErr_NoError == error) {
        DbgLog( kLogNotice, "Registered Workstation service - %s.%s", name, kWorkstationType );
        MyDNSServiceAddToRunLoop(ref);
	}
	
    return error;
}