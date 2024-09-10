void wmain( int argc, wchar_t *argv[ ])
{

//Handle the command line arguments.
LPOLESTR pszBuffer = NULL;
pszBuffer = new OLECHAR[MAX_PATH*2];
if(pszBuffer == NULL)
    goto ret;
if (argv[1] == NULL)
{
	wprintf(L"This program finds a user in the current Window 2000 domain\n");
	wprintf(L"and displays its objectSid property in string form.\n");
	wprintf(L"This program demonstrates reading a property of type octet string.\n\n");
	
	wprintf(L"Enter Common Name of the user to find:");
	if ( !_getws_s(pszBuffer, MAX_PATH*2))
	{
		delete [] pszBuffer;
		wprintf(L"String exceeded buffer size.\n\n");
		return;
	}
}
else
   if ( !wcscpy_s(pszBuffer, MAX_PATH*2, argv[1]))
   {
	    delete [] pszBuffer;
		wprintf(L"String exceeded buffer size.\n\n");
		return;
   }
//if empty string, exit.
if (0==wcscmp(L"", pszBuffer))
   goto ret;
	
wprintf(L"\nFinding user: %s...\n",pszBuffer);
	
//Intialize COM
CoInitialize(NULL);
HRESULT hr = S_OK;
//Get rootDSE and the domain container's DN.
IADs *pObject = NULL;
IDirectorySearch *pDS = NULL;
LPOLESTR szPath = NULL;
szPath = new OLECHAR[MAX_PATH];
if(szPath == NULL)
    goto ret;

VARIANT var;
hr = ADsOpenObject(L"LDAP://rootDSE",
				 NULL,
				 NULL,
				 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
				 IID_IADs,
				 (void**)&pObject);
if (FAILED(hr))
{
   wprintf(L"Not Found. Could not bind to the domain.\n");
   if (pObject)
     pObject->Release();
   goto ret;
}

VariantInit(&var);
hr = pObject->Get(L"defaultNamingContext",&var);
if (SUCCEEDED(hr))
{
	wcscpy_s(szPath,MAX_PATH,L"LDAP://");
	wcscat_s(szPath,MAX_PATH,var.bstrVal);
	VariantClear(&var);
	if (pObject)
	{
	   pObject->Release();
	   pObject = NULL;
	}
	//Bind to the root of the current domain.
	hr = ADsOpenObject(szPath,
					 NULL,
					 NULL,
					 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
					 IID_IDirectorySearch,
					 (void**)&pDS);
	if (SUCCEEDED(hr))
	{
		hr =  FindUserByName(pDS, //Container to search
						   pszBuffer, //Name of user to find.
						   &pObject); //Return a pointer to the user
		if (SUCCEEDED(hr))
		{
			//Get the objectSid property
			hr = pObject->Get(L"objectSid", &var);
			if (SUCCEEDED(hr))
			{
				LPBYTE pByte = NULL;
				wprintf (L"----------------------------------------------\n");
				wprintf (L"----------Call GetLPBYTEtoOctetString---------\n");
				wprintf (L"----------------------------------------------\n");
				hr = GetLPBYTEtoOctetString(&var, //IN. Pointer to variant containing the octetstring.
							   &pByte //OUT. Return LPBYTE to the data represented in octetstring.
							   );

				PSID pObjectSID = (PSID)pByte;
				//Convert SID to string.
				LPOLESTR szSID = NULL;
				ConvertSidToStringSid(pObjectSID, &szSID);
				wprintf(L"objectSid:%s\n",szSID);
				LocalFree(szSID);
				//Free the buffer.
				CoTaskMemFree(pByte);
			}
			else
				wprintf(L"Get method failed with hr: %x\n",hr);
			VariantClear(&var);
		}
		else
		{
            wprintf(L"User \"%s\" not Found.\n",pszBuffer);
			wprintf (L"FindUserByName failed with the following HR: %x\n", hr);
		}
		if (pObject)
			pObject->Release();
	}

	if (pDS)
	   pDS->Release();
}
ret:
    if(pszBuffer) delete pszBuffer;
    if(szPath)     delete szPath;
//Uninitalize COM
CoUninitialize();

	return;
}