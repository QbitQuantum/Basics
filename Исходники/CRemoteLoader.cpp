HMODULE CRemoteLoader::LoadLibraryFromMemory( PVOID BaseAddress, DWORD SizeOfModule, BOOL PEHeader, PCHAR OptionalPath )
{
	DebugShout( "[LoadLibraryFromMemory] BaseAddress (0x%X) - SizeOfModule (0x%X)", BaseAddress, SizeOfModule );

	IMAGE_NT_HEADERS* ImageNtHeaders = ToNts( BaseAddress );

	if( ImageNtHeaders == NULL )
	{
		DebugShout( "[LoadLibraryFromMemory] Invalid Image: No IMAGE_NT_HEADERS" );

		return NULL;
	}

	DebugShout( "[LoadLibraryFromMemory] SizeOfImage (0x%X)", ImageNtHeaders->OptionalHeader.SizeOfImage );

	if( ImageNtHeaders->FileHeader.NumberOfSections == 0 )
	{
		DebugShout( "[LoadLibraryFromMemory] Invalid Image: No Sections" );

		return NULL;
	}

	if( ( ImageNtHeaders->OptionalHeader.ImageBase % 4096 ) != 0 )
	{
		DebugShout( "[LoadLibraryFromMemory] Invalid Image: Not Page Aligned" );
		
		return NULL;
	}

	if( ImageNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ].Size )
	{
		if( ImageDirectoryEntryToData( BaseAddress, IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ) )
		{
			DebugShout( "[LoadLibraryFromMemory] This method is not supported for Managed executables!" );

			return NULL;
		}
	}

	DebugShout( "[LoadLibraryFromMemory] No COM/CLR data found!" );

	// SizeOfImage NOT the same as module size M**********R
	// http://www.youtube.com/watch?v=pele5vptVgc

	PVOID AllocatedRemoteMemory = RemoteAllocateMemory( ImageNtHeaders->OptionalHeader.SizeOfImage );

	if( AllocatedRemoteMemory == NULL )
	{
		DebugShout( "[LoadLibraryFromMemory] Failed to allocate remote memory for module!" );

		return NULL;
	}

	DebugShout( "[LoadLibraryFromMemory] Allocated remote module at [0x%X]!", AllocatedRemoteMemory );

	if( ProcessImportTable( BaseAddress, AllocatedRemoteMemory, OptionalPath ) == FALSE )
	{
		DebugShout( "[LoadLibraryFromMemory] Failed to fix imports!" );

		return NULL;
	}

	DebugShout( "[LoadLibraryFromMemory] Fixed Imports!" );

	if( ProcessRelocations( BaseAddress, AllocatedRemoteMemory ) == FALSE )
	{
		DebugShout( "[LoadLibraryFromMemory] Failed to process relocations!" );

		RemoteFreeMemory( AllocatedRemoteMemory, SizeOfModule );

		return NULL;
	}

	DebugShout( "[LoadLibraryFromMemory] Fixed Relocations!" );

	if( ProcessSections( BaseAddress, AllocatedRemoteMemory, PEHeader ) == FALSE )
	{
		DebugShout( "[LoadLibraryFromMemory] Failed to process sections!" );
	}

	DebugShout( "[LoadLibraryFromMemory] Processed sections!" );

	if( ProcessTlsEntries( BaseAddress, AllocatedRemoteMemory ) == FALSE )
	{
		DebugShout( "[LoadModuleFromMemory] ProcessTlsEntries Failed!" );

		// we can also choose to continue here..

		return NULL;
	}

	DebugShout( "[LoadModuleFromMemory] Processed Tls Entries!" );

	if( ImageNtHeaders->OptionalHeader.AddressOfEntryPoint )
	{
		FARPROC DllEntryPoint = MakePtr( FARPROC, AllocatedRemoteMemory, ImageNtHeaders->OptionalHeader.AddressOfEntryPoint );

		DebugShout( "[LoadModuleFromMemory] DllEntrypoint = 0x%X", DllEntryPoint );

		if( CallEntryPoint( AllocatedRemoteMemory, DllEntryPoint ) == false )
		{
			DebugShout( "[LoadModuleFromMemory] Failed to execute remote thread buffer" );
		}
		else
		{
			DebugShout( "[LoadModuleFromMemory] Executed the remote thread buffer successfully [0x%X]", DllEntryPoint );
		}
	}
	else
	{
		DebugShout( "[LoadModuleFromMemory] AddressOfEntryPoint is NULL" );
	}

	DebugShout( "[LoadModuleFromMemory] Returning Pointer (0x%X)", AllocatedRemoteMemory );

	return ( HMODULE ) AllocatedRemoteMemory;
}