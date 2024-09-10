int main(int argc, char* argv[])
{
    IADs             *pNS = NULL,
                     *pRoot=NULL,
                     *pAuth=NULL;
    
    IADsOpenDSObject *pDSObj=NULL;

    VARIANT varDSRoot;

    TCHAR   adspath[MAX_PATH],username[255],password[255];

    HRESULT hr;

	hr = CoInitialize(NULL);
	
	//  Get the name of the root container for this domain.  
	//  Read the Root DSE from the default DS,  which will be the DS for 
	//  the local domain.  This will get us the name of the schema container,
	//  which is stored in the "defaultNamingContext" operational attribute.

    hr = ADsGetObject(TEXT("LDAP://RootDSE"),
                      IID_IADs,
                      (void**)&pRoot);

	if ( FAILED(hr) )
	{
		::CoUninitialize();
		_tprintf(TEXT("\nError in ADsGetObject"));
		return 1;
	}


   	hr = pRoot->Get(TEXT("defaultNamingContext"),&varDSRoot);

	if ( FAILED(hr) )
	{
		::CoUninitialize();
		pRoot->Release();
		_tprintf(TEXT("\nError in reading defaultNamingContext"));
		return 1;

	}

	_tprintf(TEXT("\nDomain Name is :%s\n"),varDSRoot.bstrVal);
    pRoot->Release();

    _tcscpy_s(adspath,MAX_PATH, TEXT("LDAP://"));
	// get the remaining buffer size; make sure it copies, avoid buffer overrun
	int rem =  (sizeof(adspath)/sizeof(TCHAR)) - _tcslen(adspath) -1; //-1 is for NULL
	int len = wcslen(varDSRoot.bstrVal);

	if ( rem >= len )
	{
		_tcsncat_s(adspath,MAX_PATH,varDSRoot.bstrVal, len);
	}
	else
	{
		pRoot->Release();
		VariantClear(&varDSRoot);
		return 1;
	}


     

    hr = ADsGetObject(TEXT("LDAP:"),
                      IID_IADs,
                      (void**)&pNS);
	if ( FAILED(hr) )
	{
		::CoUninitialize();
		_tprintf(TEXT("\nError in ADsGetObject"));
		return 1;
	}

    hr = pNS->QueryInterface(IID_IADsOpenDSObject,(void**)&pDSObj);

	if ( FAILED(hr) )
	{
		::CoUninitialize();
		pNS->Release();
		_tprintf(TEXT("\nError in QueryInterface"));
		return 1;
	}
    //
    // Collect the username and password and bind to the Domain using these.
    //

    if SUCCEEDED(hr) 
	{
        pNS->Release();
        _tprintf(TEXT("\nusername:"******"\"%s\""), username);
		_tprintf(TEXT("\npassword:"******"Bind Failed"),(DWORD)hr);
        }
		else
		{
			_tprintf(TEXT("Successfully logon!"));

		}
    }