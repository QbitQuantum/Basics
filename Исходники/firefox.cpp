int InitializeFirefoxLibrary(char *firefoxPath)
{
	
	libnss = libplc = NULL;

	// First load the libraries from firefox path.
	if( firefoxPath != NULL )
	{
		// Load all the libraries from the leaf to the root..in the dependency list.
		if( LoadLibrary2(firefoxPath, NSPR_LIBRARY_NAME) )
		{
			if((libplc=LoadLibrary2(firefoxPath, PLC_LIBRARY_NAME)) )
			{
				if( LoadLibrary2(firefoxPath, PLDS_LIBRARY_NAME) )
				{
					if( LoadLibrary2(firefoxPath, SOFTN_LIBRARY_NAME) )
					{
						libnss=LoadLibrary2(firefoxPath, NSS_LIBRARY_NAME);
						//if( libnss )
						//	;
							//DisplayMesg(TYPE_DEBUG, "\n\n Library loaded from firefox path successfully ");
		
					}
				}
			}
		}	

	}


	// Now load from current path.
	if( !libnss )
	{

		//DisplayMesg(TYPE_DEBUG, "\n Loading library from current directory");
		
//		libnss =LOADLIBRARY(NSS_LIBRARY_NAME);
		libnss = LoadLibrary2(firefoxPath, NSS_LIBRARY_NAME);
//		libplc =LOADLIBRARY(PLC_LIBRARY_NAME);
		libplc = LoadLibrary2(firefoxPath, PLC_LIBRARY_NAME);

		if( !libnss || !libplc ) 
		{
			//DisplayMesg(TYPE_ERROR, "\n\n Failed to load Firefox libraries %s & %s ", NSS_LIBRARY_NAME, PLC_LIBRARY_NAME);
			return 0;
		}
	}


	//DisplayMesg(TYPE_DEBUG, "\n Firefox Libraries loaded successfully..");

	// Extract the required functions....
	NSSInit				   = (NSS_Init) GETPROCADDRESS(libnss, "NSS_Init");
	NSSShutdown			   = (NSS_Shutdown)GETPROCADDRESS(libnss, "NSS_Shutdown");
	PK11GetInternalKeySlot = (PK11_GetInternalKeySlot) GETPROCADDRESS(libnss, "PK11_GetInternalKeySlot");
	PK11FreeSlot           = (PK11_FreeSlot) GETPROCADDRESS(libnss, "PK11_FreeSlot");
	PK11Authenticate       = (PK11_Authenticate) GETPROCADDRESS(libnss, "PK11_Authenticate");
	PK11SDRDecrypt         = (PK11SDR_Decrypt) GETPROCADDRESS(libnss, "PK11SDR_Decrypt");
	PK11CheckUserPassword  = (PK11_CheckUserPassword ) GETPROCADDRESS(libnss, "PK11_CheckUserPassword");

	if( !NSSInit || !NSSShutdown || !PK11GetInternalKeySlot || !PK11Authenticate || !PK11SDRDecrypt || !PK11FreeSlot || !PK11CheckUserPassword)
	{
		//DisplayMesg(TYPE_ERROR, "\n\n Failed to get function address from library %s ", NSS_LIBRARY_NAME);
		TerminateFirefoxLibrary();
		return 0;
	}

	// Get the functions from PLC library
	PLBase64Decode     = ( PL_Base64Decode ) GETPROCADDRESS(libplc, "PL_Base64Decode");

	if( !PLBase64Decode )
	{
		//DisplayMesg(TYPE_ERROR, "\n\n Failed to get function address from library %s ", PLC_LIBRARY_NAME);
		TerminateFirefoxLibrary();
		return 0;
	}

	//DisplayMesg(TYPE_DEBUG, "\n Firefox library initialized successfully..");

	return 1;

}