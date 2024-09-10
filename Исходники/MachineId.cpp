unsigned long long loadngo::data::GetMachineId()
{
	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------
//	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
//	if (hr == S_OK)
//	{
		BSTR objectPath = SysAllocString(L"ROOT\\CIMV2");
		std::vector<char> container;
		// Step 2: --------------------------------------------------
		// Set general COM security levels --------------------------
		// Note: If you are using Windows 2000, you need to specify -
		// the default authentication credentials for a user by using
		// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
		// parameter of CoInitializeSecurity ------------------------

		HRESULT hr = CoInitializeSecurity(
			NULL,
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
			);


		if (hr == S_OK)
		{

			// Step 3: ---------------------------------------------------
			// Obtain the initial locator to WMI -------------------------

			IWbemLocator *pLoc = NULL;

			hr = CoCreateInstance(
				CLSID_WbemLocator,
				0,
				CLSCTX_INPROC_SERVER,
				IID_IWbemLocator, (LPVOID *)&pLoc);

			if (hr == S_OK)
			{

				// Step 4: -----------------------------------------------------
				// Connect to WMI through the IWbemLocator::ConnectServer method

				IWbemServices *pSvc = NULL;

				// Connect to the root\cimv2 namespace with
				// the current user and obtain pointer pSvc
				// to make IWbemServices calls.
				hr = pLoc->ConnectServer(
					objectPath, // Object path of WMI namespace
					NULL,                    // User name. NULL = current user
					NULL,                    // User password. NULL = current
					0,                       // Locale. NULL indicates current
					NULL,                    // Security flags.
					0,                       // Authority (e.g. Kerberos)
					0,                       // Context object 
					&pSvc                    // pointer to IWbemServices proxy
					);

				if (hr == S_OK)
				{

					// Step 5: --------------------------------------------------
					// Set security levels on the proxy -------------------------

					hr = CoSetProxyBlanket(
						pSvc,                        // Indicates the proxy to set
						RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
						RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
						NULL,                        // Server principal name 
						RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
						RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
						NULL,                        // client identity
						EOAC_NONE                    // proxy capabilities 
						);

					if (hr == S_OK)
					{
						// Step 6: --------------------------------------------------
						// Use the IWbemServices pointer to make requests of WMI ----
						BSTR wql = SysAllocString(L"WQL");
						BSTR query = SysAllocString(L"SELECT * FROM Win32_BIOS");
						// For example, get the name of the operating system
						IEnumWbemClassObject* pEnumerator = NULL;
						hr = pSvc->ExecQuery(
							wql,
							query,
							WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
							NULL,
							&pEnumerator);

						if (hr == S_OK)
						{
							// Step 7: -------------------------------------------------
							// Get the data from the query in step 6 -------------------

							IWbemClassObject *pclsObj = NULL;
							ULONG uReturn = 0;

							while (pEnumerator)
							{
								hr = pEnumerator->Next(WBEM_INFINITE, 1,
									&pclsObj, &uReturn);

								if (0 == uReturn)
								{
									break;
								}

								if(pclsObj->BeginEnumeration(0) == S_OK)
								{
									BSTR name = nullptr;
									VARIANT var;
									while (pclsObj->Next(0, &name, &var, nullptr, nullptr) == WBEM_S_NO_ERROR)
									{
										Insert(container, name);
										SysFreeString(name);
										InsertVariant(container, var);
										VariantClear(&var);
									}
								}

								pclsObj->Release();
							}
						}
						pEnumerator->Release();
					}
					pSvc->Release();
					pSvc = 0;
				}
				pLoc->Release();
			}
		}
		SysFreeString(objectPath);
	//	CoUninitialize();
	//}
	return util::FNV1a(&container[0], container.size());
}