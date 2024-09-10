BOOL WINAPI EnumerateFunc(LPNETRESOURCE lpnr)
{
	DWORD dwResult, dwResultEnum;
	HANDLE hEnum;
	DWORD cbBuffer = 16384;  // 16K is a good size
	DWORD cEntries = -1;	 // enumerate all possible entries
	LPNETRESOURCE lpnrLocal; // pointer to enumerated structures
	DWORD i;
	//
	// Call the WNetOpenEnum function to begin the enumeration.
	//
	dwResult = WNetOpenEnum(RESOURCE_CONNECTED /*RESOURCE_GLOBALNET*/, // all network resources
							RESOURCETYPE_ANY,						   // all resources
							0,										   // enumerate all resources
							lpnr,									   // NULL first time the function is called
							&hEnum);								   // handle to the resource

	if (dwResult != NO_ERROR) {
		//
		// Process errors with an application-defined error handler.
		//
		//NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
		return FALSE;
	}
	//
	// Call the GlobalAlloc function to allocate resources.
	//
	lpnrLocal = (LPNETRESOURCE)GlobalAlloc(GPTR, cbBuffer);

	do {
		//
		// Initialize the buffer.
		//
		ZeroMemory(lpnrLocal, cbBuffer);
		//
		// Call the WNetEnumResource function to continue
		//  the enumeration.
		//
		dwResultEnum = WNetEnumResource(hEnum,		// resource handle
										&cEntries,  // defined locally as -1
										lpnrLocal,  // LPNETRESOURCE
										&cbBuffer); // buffer size
		//
		// If the call succeeds, loop through the structures.
		//
		if (dwResultEnum == NO_ERROR) {
			for (i = 0; i < cEntries; i++) {
				// Call an application-defined function to
				//  display the contents of the NETRESOURCE structures.
				//
				DisplayStruct(&lpnrLocal[i]);

				// If the NETRESOURCE structure represents a container resource,
				//  call the EnumerateFunc function recursively.

				if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER))
					if (!EnumerateFunc(&lpnrLocal[i]))
						return FALSE;
				//TextOut(hdc, 10, 10, "EnumerateFunc returned FALSE.", 29);
			}
		}
		// Process errors.
		//
		else if (dwResultEnum != ERROR_NO_MORE_ITEMS) {
			//NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
			break;
		}
	}
	//
	// End do.
	//
	while (dwResultEnum != ERROR_NO_MORE_ITEMS);
	//
	// Call the GlobalFree function to free the memory.
	//
	GlobalFree((HGLOBAL)lpnrLocal);
	//
	// Call WNetCloseEnum to end the enumeration.
	//
	dwResult = WNetCloseEnum(hEnum);

	if (dwResult != NO_ERROR) {
		//
		// Process errors.
		//
		//NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
		return FALSE;
	}

	return TRUE;
}