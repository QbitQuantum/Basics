	static
	ce::wstring
	IPAddressString(
		)
	{
		ce::auto_ptr<IP_ADAPTER_ADDRESSES>		AdapterAddresses;  // buffer used by GetAdaptersAddresses()
		ULONG					BufferSize = 0;    // size of buffer returned by GetAdaptersAddresses()
		DWORD					Result  = 0;   // result codes from iphelper apis
		WCHAR					NetworkAddress[ s_MAXNETADDRLEN ];
		DWORD					AddressLen = s_MAXNETADDRLEN;

		// Find out size of returned buffer
		Result = GetAdaptersAddresses(
					AF_INET,
					GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_SERVER,
					NULL,
					AdapterAddresses,
					&BufferSize
					);
	    
		if(BufferSize)
		{
			// Allocate sufficient Space
			AdapterAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(operator new (BufferSize));
			if (AdapterAddresses != NULL)
			{
				// Get Adapter List
				Result = GetAdaptersAddresses(
					AF_INET, 
					GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_SERVER,
					NULL,
					AdapterAddresses,
					&BufferSize
					);

				if (Result == ERROR_SUCCESS)
				{
					// Loop through all the adapters (interfaces) returned
					for(PIP_ADAPTER_ADDRESSES pAdapterIter = AdapterAddresses; pAdapterIter != NULL; pAdapterIter = pAdapterIter->Next)
					{
						// don't use tunneling adapters
						if(pAdapterIter->IfType == IF_TYPE_SOFTWARE_LOOPBACK)
						{
							continue;
						}

						// Loop through all the addresses returned
						for(PIP_ADAPTER_UNICAST_ADDRESS pUnicastAddress = pAdapterIter->FirstUnicastAddress;
							pUnicastAddress != NULL;
							pUnicastAddress = pUnicastAddress->Next)
						{
							if(((PSOCKADDR_IN)pUnicastAddress->Address.lpSockaddr)->sin_addr.S_un.S_addr)
							{
								//Convert from Address to string
								SOCKADDR sa;
								sa = *(pUnicastAddress->Address.lpSockaddr);
								if (WSAAddressToStringW(
										&sa,
										pUnicastAddress->Address.iSockaddrLength,
										NULL,
										NetworkAddress,
										&AddressLen) == 0) //success
								{
									return	ce::wstring( NetworkAddress );
								}
							}
						}
					}
				}
			}
		}
			
		return ce::wstring();
	}