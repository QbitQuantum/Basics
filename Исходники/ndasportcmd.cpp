BOOL 
ProcessPlugIn(
	NDAS_LOGICALUNIT_ADDRESS Address,
	int argc, 
	TCHAR** argv)
{
	if (argc < 1)
	{
		usage();
		return FALSE;
	}

	PNDAS_LOGICALUNIT_DESCRIPTOR logicalUnitDescriptor = NULL;

	if (0 == lstrcmpi(_T("filedisk"), argv[0]))
	{
		if (argc != 4 )
		{
			usage();
			return FALSE;
		}

		LPCTSTR filePath = argv[1];
		// const WCHAR FileNamePrefix[] = L"\\\\?\\";
		const WCHAR FileNamePrefix[] = L"\\??\\";

#ifdef UNICODE

		DWORD fileFullPathLength = GetFullPathName(filePath, 0, NULL, NULL);
		if (0 == fileFullPathLength)
		{
			_tprintf(_T("Error: GetFullPathName failed!\n"));
			return FALSE;
		}

		fileFullPathLength += RTL_NUMBER_OF(FileNamePrefix);

		LPWSTR fileFullPathBuffer = static_cast<LPWSTR>(HeapAlloc(
			GetProcessHeap(),
			HEAP_ZERO_MEMORY,
			fileFullPathLength * sizeof(WCHAR)));

		if (!fileFullPathBuffer)
		{
			_tprintf(_T("Error: Out of memory!\n"));
			SetLastError(ERROR_OUTOFMEMORY);
			return FALSE;
		}

		LPWSTR fileFullPath = NULL;

		size_t remainingLength = 0;

		StringCchCopyExW(
			fileFullPathBuffer,
			fileFullPathLength,
			FileNamePrefix,
			&fileFullPath,
			&remainingLength,
			STRSAFE_IGNORE_NULLS);

		GetFullPathName(
			filePath, 
			static_cast<DWORD>(remainingLength), 
			fileFullPath,
			NULL);

#else
		C_ASSERT(FALSE && "not implemented");
#endif
		_tprintf(_T("File Name=%s\n"), fileFullPathBuffer);
		_tprintf(_T("Length=%d bytes\n"), fileFullPathLength * sizeof(WCHAR));

		DWORD descriptorLength = 
			FIELD_OFFSET(FILEDISK_DESCRIPTOR, FilePath) +
			fileFullPathLength * sizeof(WCHAR);

		PFILEDISK_DESCRIPTOR descriptor = 
			static_cast<PFILEDISK_DESCRIPTOR>(
				HeapAlloc(
					GetProcessHeap(),
					HEAP_ZERO_MEMORY,
					descriptorLength));

		if (NULL == descriptor)
		{
			_tprintf(_T("Error: Out of memory!\n"));
			HeapFree(GetProcessHeap(), 0, fileFullPathBuffer);
			SetLastError(ERROR_OUTOFMEMORY);
			return FALSE;
		}

		descriptor->Header.Version = sizeof(NDAS_LOGICALUNIT_DESCRIPTOR);
		descriptor->Header.Size = descriptorLength;
		descriptor->Header.Address = Address;
		descriptor->Header.Type = NdasExternalType;
		descriptor->Header.ExternalTypeGuid = NDASPORT_FILEDISK_TYPE_GUID;

		descriptor->LogicalBlockAddress.QuadPart = 750LL * 1024LL * 1024LL * 1024LL / 512LL;
		descriptor->BytesPerBlock = 512;
		descriptor->FileDiskFlags = FILEDISK_FLAG_USE_SPARSE_FILE;

		CopyMemory(
			descriptor->FilePath,
			fileFullPathBuffer,
			fileFullPathLength * sizeof(WCHAR));

		HeapFree(GetProcessHeap(), 0, fileFullPathBuffer);

		logicalUnitDescriptor = 
			reinterpret_cast<PNDAS_LOGICALUNIT_DESCRIPTOR>(
				static_cast<PFILEDISK_DESCRIPTOR>(descriptor));
	}
	else if (0 == lstrcmpi(_T("ramdisk"), argv[0]))
	{
		return TRUE;
	}
	else if (0 == lstrcmpi(_T("ndasdlu"), argv[0]))
	{
		logicalUnitDescriptor = ProcessPlugIn_Dlu(Address, argc - 1, argv + 1);

		if (NULL == logicalUnitDescriptor)
		{
			return FALSE;
		}
	}
	else
	{
		//
		// Reserve 2MB from the end
		//
		LARGE_INTEGER logicalBlockAddress;
		logicalBlockAddress.QuadPart = -2 * 1024 * 1024 / 512;

		NDAS_DEVICE_IDENTIFIER ndasDeviceIdentifier;
		BOOL success = ParseNdasDeviceId(argv[0], &ndasDeviceIdentifier);

		if (!success)
		{
			_tprintf(_T("Error: NDAS Device Identifier is invalid.\n\n"));
			usage();
			return FALSE;
		}

		ACCESS_MASK accessMode;
		if (0 == lstrcmpi(_T("ro"), argv[1]))
		{
			accessMode = GENERIC_READ;
		}
		else if (0 == lstrcmpi(_T("rw"), argv[1]))
		{
			accessMode = GENERIC_READ | GENERIC_WRITE;
		}
		else
		{
			_tprintf(_T("Error: Access mode is invalid or not specified.\n\n"));
			usage();
			return FALSE;
		}

		if (argc > 2 && 0 == lstrcmpi(_T("noreserve"), argv[2]))
		{
			logicalBlockAddress.QuadPart = 0;
			_tprintf(_T("No reserve mode\n"));
		}

#ifdef _DEBUG
		_tprintf(_T("(%d,%d,%d) %02X-%02X-%02X-%02X-%02X-%02X %d\n"),
				 Address.PathId,
				 Address.TargetId,
				 Address.Lun,			
				 ndasDeviceIdentifier.Identifier[0],
				 ndasDeviceIdentifier.Identifier[1],
				 ndasDeviceIdentifier.Identifier[2],
				 ndasDeviceIdentifier.Identifier[3],
				 ndasDeviceIdentifier.Identifier[4],
				 ndasDeviceIdentifier.Identifier[5],
				 ndasDeviceIdentifier.UnitNumber);
#endif

		logicalUnitDescriptor = NdasPortCtlBuildNdasAtaDeviceDescriptor(
			Address,
			0,
			&ndasDeviceIdentifier,
			0, 
			0,
			accessMode,
			0,
			&logicalBlockAddress);

		if (NULL == logicalUnitDescriptor)
		{
			_tprintf(_T("Error: Out of memory!\n"));
			return FALSE;
		}
	}
	
	_ASSERT(NULL != logicalUnitDescriptor);

	XTL::AutoProcessHeap logicalUnitDescriptorPtr = logicalUnitDescriptor;

	XTL::AutoFileHandle handle = NdasPortCtlCreateControlDevice(GENERIC_READ | GENERIC_WRITE);
	if (handle.IsInvalid())
	{
		ErrorHolder lastError;
		
		_tprintf(_T("Opening NDAS Port device file failed.\n"));
		_tprintf(_T("Error %u (0x%X): %hs\n"), 
			lastError.GetCode(), 
			lastError.GetCode(), 
			lastError.GetDescriptionA());

		return FALSE;
	}

	BOOL success = NdasPortCtlGetPortNumber(
		handle, 
		&logicalUnitDescriptor->Address.PortNumber);

	if (!success)
	{
		ErrorHolder lastError;

		_tprintf(_T("Getting the port number failed.\n"));
		_tprintf(_T("Error %u (0x%X): %hs\n"), 
			lastError.GetCode(), 
			lastError.GetCode(), 
			lastError.GetDescriptionA());
		return FALSE;
	}

	success = NdasPortCtlPlugInLogicalUnit(
		handle,
		logicalUnitDescriptor);

	if (!success)
	{
		ErrorHolder lastError;

		_tprintf(_T("PlugIn failed.\n"));
		_tprintf(_T("Error %u (0x%X): %hs\n"), 
			lastError.GetCode(), 
			lastError.GetCode(), 
			lastError.GetDescriptionA());
		return FALSE;
	}

	return TRUE;
}