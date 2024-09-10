STDMETHODIMP CDNSSD::Resolve(DNSSDFlags flags, ULONG ifIndex, BSTR serviceName, BSTR regType, BSTR domain, IResolveListener* listener, IDNSSDService** service)
{
	CComObject<CDNSSDService>	*	object			= NULL;
	std::string						serviceNameUTF8;
	std::string						regTypeUTF8;
	std::string						domainUTF8;
	DNSServiceRef					sref			= NULL;
	DNSServiceErrorType				err				= 0;
	HRESULT							hr				= 0;
	BOOL							ok;

	// Initialize
	*service = NULL;

	// Convert BSTR params to utf8
	ok = BSTRToUTF8( serviceName, serviceNameUTF8 );
	require_action( ok, exit, err = kDNSServiceErr_BadParam );
	ok = BSTRToUTF8( regType, regTypeUTF8 );
	require_action( ok, exit, err = kDNSServiceErr_BadParam );
	ok = BSTRToUTF8( domain, domainUTF8 );
	require_action( ok, exit, err = kDNSServiceErr_BadParam );

	try
	{
		object = new CComObject<CDNSSDService>();
	}
	catch ( ... )
	{
		object = NULL;
	}

	require_action( object != NULL, exit, err = kDNSServiceErr_NoMemory );
	hr = object->FinalConstruct();
	require_action( hr == S_OK, exit, err = kDNSServiceErr_Unknown );
	object->AddRef();

	err = DNSServiceResolve( &sref, flags, ifIndex, serviceNameUTF8.c_str(), regTypeUTF8.c_str(), domainUTF8.c_str(), ( DNSServiceResolveReply ) &ResolveReply, object );
	require_noerr( err, exit );

	object->SetServiceRef( sref );
	object->SetListener( listener );

	err = object->Run();
	require_noerr( err, exit );

	*service = object;

exit:

	if ( err && object )
	{
		object->Release();
	}

	return err;
}