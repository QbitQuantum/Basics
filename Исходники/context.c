HRESULT JpfsvLoadModuleContext(
	__in JPFSV_HANDLE ContextHandle,
	__in PCWSTR ModulePath,
	__in_opt PCWSTR Alias,
	__in DWORD_PTR LoadAddress,
	__in_opt DWORD SizeOfDll
	)
{
	PJPFSV_CONTEXT Context = ( PJPFSV_CONTEXT ) ContextHandle;
	DWORD64 ImgLoadAddress;

	if ( ! Context ||
		 Context->Signature != JPFSV_CONTEXT_SIGNATURE ||
		 ! ModulePath ||
		 ! LoadAddress )
	{
		return E_INVALIDARG;
	}

	EnterCriticalSection( &JpfsvpDbghelpLock );

	ImgLoadAddress = SymLoadModuleEx(
		Context->ProcessHandle,
		NULL,
		ModulePath,
		Alias,
		LoadAddress,
		SizeOfDll,
		NULL,
		0 );

	LeaveCriticalSection( &JpfsvpDbghelpLock );

	if ( 0 == ImgLoadAddress )
	{
		DWORD Err = GetLastError();
		
		if ( ERROR_SUCCESS == Err )
		{
			//
			// This seems to mean that the module has already been
			// loaded.
			//
			return S_FALSE;
		}
		else
		{
			return HRESULT_FROM_WIN32( Err );
		}
	}

	return S_OK;
}