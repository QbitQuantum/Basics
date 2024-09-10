BOOL RequestLicenseKey(BSTR& bstrLicenseKey, CString strProgID)
{
	USES_CONVERSION;
	
	LPCLASSFACTORY2 pClassFactory;
	CLSID clsid;
	BOOL bValidKeyReturned = FALSE;

	// Get the CLSID of the specified ProgID
	if (SUCCEEDED(CLSIDFromProgID(T2OLE(strProgID), &clsid)))
	{
		// Create an instance of the object and query it for
		//  the IClassFactory2 interface.
		if (SUCCEEDED(CoGetClassObject(clsid, CLSCTX_INPROC_SERVER, NULL,
			IID_IClassFactory2, (LPVOID *)(&pClassFactory))))
        {
			LICINFO licinfo;

			// Check to see if this object has a runtime license key
            if (SUCCEEDED(pClassFactory->GetLicInfo(&licinfo)))
			{
				if (licinfo.fRuntimeKeyAvail)
				{
					HRESULT hr;
					
					// The object has a runtime license key so request it
					hr = pClassFactory->RequestLicKey(0, &bstrLicenseKey);
					
					if (SUCCEEDED(hr))
					{
						if(bstrLicenseKey == NULL)
                            bstrLicenseKey = ::SysAllocString(
                                L"<Object returned a NULL license key>");
						else
							// We got the license key!
							bValidKeyReturned = TRUE;
					}
					else
						// Requesting the license key failed
						switch(hr)
						{
							case E_NOTIMPL:
								bstrLicenseKey = ::SysAllocString(
                                    L"<The object's class factory does not support"
                                    L" run-time license keys>");
								break;

							case E_UNEXPECTED:
								bstrLicenseKey = ::SysAllocString(
                                    L"<An unexpected error occurred when requesting"
                                    L" the run-time license key>");
								break;

							case E_OUTOFMEMORY:
								bstrLicenseKey = ::SysAllocString(
                                    L"<The object's class factory was unable to"
                                    L" allocate the license key>");
								break;

							case CLASS_E_NOTLICENSED:
								bstrLicenseKey = ::SysAllocString(
                                    L"<The object's class factory supports run-time"
                                    L" licensing, but the current machine\r\nitself"
                                    L" is not licensed. Thus, a run-time key is not"
                                    L" available on this machine>");
								break;

							default:
								bstrLicenseKey = ::SysAllocString(
                                    L"<An unknown error occurred when requesting"
                                    L" the license key>");
						}
				}
				else
					bstrLicenseKey = ::SysAllocString(
                        L"<The object has no runtime license key>");
			}
			else
				bstrLicenseKey = ::SysAllocString(
                    L"<Unable to get the licensing capabilities of the"
                    L" object's class factory>");

			// Make sure we release the reference to the class factory
			pClassFactory->Release();
		}
		else
			bstrLicenseKey = ::SysAllocString(
                L"<Unable to get the IClassFactory2 interface from the specified object>");
	}
	else
		bstrLicenseKey = ::SysAllocString(
            L"<Unable to get the CLSID of the specified object>");
	
	// Return a BOOL specifying whether or not we were able to get a
	//  valid license key
	return bValidKeyReturned;
}