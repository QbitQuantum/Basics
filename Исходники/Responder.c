static DNSServiceErrorType RegisterService(RegisteredService *rs, mDNSOpaque16 OpaquePort,
	const char name[], const char type[], const char domain[], const char txtinfo[])
	{
	DNSServiceErrorType err;
	unsigned char txtbuffer[257];
	strncpy((char*)txtbuffer+1, txtinfo, 255);
	txtbuffer[256] = 0;
	txtbuffer[0] = (unsigned char)strlen((char*)txtbuffer);
	rs->gotresult = 0;
	rs->errorCode = kDNSServiceErr_NoError;
	err = DNSServiceRegister(&rs->sdRef, /* kDNSServiceFlagsAutoRename*/ 0, 0,
		name, type, domain, NULL, OpaquePort.NotAnInteger, (unsigned short)(1+txtbuffer[0]), txtbuffer, RegCallback, rs);
	if (err)
		printf("RegisterService(%s %s %s) failed %d\n", name, type, domain, err);
	else
		{ *nextservice = rs; nextservice = &rs->next; }
	return(err);
	}