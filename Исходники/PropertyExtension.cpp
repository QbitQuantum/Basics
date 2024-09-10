// IIntitializeWithFile methods implementations
IFACEMETHODIMP PropertyExtension::Initialize(LPCWSTR pszFilePath, DWORD grfMode)
{
	// Make sure initialization is only done once
	if (m_bAlreadyInitialized)
		return HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED);
	
	m_bAlreadyInitialized = true;

	if (pszFilePath == NULL)
		return E_INVALIDARG;		// What are we supposed to do with NULL filename string?

	// Make sure COM has been properly initialized for this thread
	if (!m_bCOMInitialized)
		return E_UNEXPECTED;

	// We now do our own initialization
	wstring Filename(pszFilePath);
	const int BUFFER_SIZE = 8;
	BYTE pData[BUFFER_SIZE];
	CComPtr<IStream> pStream;

	// Create a stream out of this filepath
	if (FAILED(SHCreateStreamOnFileEx(pszFilePath, STGM_READ, FILE_ATTRIBUTE_NORMAL, FALSE, NULL, &pStream)))
		return E_FAIL;

	// Go through filename and stream then collect data
	//	which will be returned in 'GetValue()'

	// Check extension to determine type of file
	size_t ExtensionPos = Filename.find_last_of(L".");
	if (ExtensionPos == Filename.size() - 1)
		return E_NOTIMPL;
	else
		ExtensionPos++;

	wstring FileExtension = Filename.substr(ExtensionPos);
	transform(FileExtension.begin(), FileExtension.end(), FileExtension.begin(), ::tolower);	// Make file extension lowercase

	if (FileExtension == L"exe")
			m_Format = EXE;
	else if (FileExtension == L"dll")
			m_Format = DLL;
	else if ((FileExtension == L"obj") || (FileExtension == L"o"))
			m_Format = OBJ;
	else if ((FileExtension == L"lib") || (FileExtension == L"a"))
			m_Format = LIB;
	else
		return E_NOTIMPL;

	// According to the format, read data
	ULONG cbRead = 0;
	LARGE_INTEGER pos = { 0 };

	SEEK(pStream, pos, STREAM_SEEK_SET);			// Reset file pointer

	switch (m_Format)
	{
		case EXE:
		case DLL:
		{
			m_cSupportedProperties = NUM_OF_ADDED_PROPERTIES;

			// Check MZ header			
			READ(pStream, sizeof(WORD));
			if (cast<WORD>(pData) != IMAGE_DOS_SIGNATURE)	// Check MSDOS signature
			{
				m_Format = Invalid;
				return S_OK;
			}

			// Check PE header
			pos.QuadPart = 0x3C;	// Offset to PE header is always at 0x3C
			SEEK(pStream, pos, STREAM_SEEK_SET);
			READ(pStream, sizeof(DWORD));
			pos.QuadPart = cast<DWORD>(pData);
			if (pos.QuadPart == 0)
			{
				m_Format = Invalid;
				return S_OK;
			}

			SEEK(pStream, pos, STREAM_SEEK_SET);
			READ(pStream, sizeof(DWORD));
			if (cast<DWORD>(pData) != IMAGE_NT_SIGNATURE)
			{
				m_Format = Invalid;
				return S_OK;
			}

			// Find PE type field
			pos.QuadPart = 20;
			SEEK(pStream, pos, STREAM_SEEK_CUR);
			READ(pStream, sizeof(WORD));
			switch (cast<WORD>(pData))
			{
				case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
					m_ArchType = _32bit;

					break;

				case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
					m_ArchType = _64bit;

					break;

				default:	// Who uses ROM PEs anyway?
					m_Format = Invalid;
					return S_OK;
			}

			// Find PE subsystem field
			pos.QuadPart = 66;
			SEEK(pStream, pos, STREAM_SEEK_CUR);
			READ(pStream, sizeof(WORD));
			switch (cast<WORD>(pData))
			{
				case IMAGE_SUBSYSTEM_NATIVE:
					m_SubsysType = Native;

					break;

				case IMAGE_SUBSYSTEM_WINDOWS_CUI:
					m_SubsysType = CUI;

					break;

				case IMAGE_SUBSYSTEM_WINDOWS_GUI:
				case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
					m_SubsysType = GUI;

					break;

				default:
					m_Format = Invalid;
					return S_OK;
			}

			// NOTE: Previous property handler may fail if 'Resource Directory'
			//	does not exist for this PE file. But we don't want to just fail
			//	because of this. So, if this directory is empty don't bother
			//	initializing previous handler and handle everything.

			// First read no. of data directory
			switch (m_ArchType)
			{
				case _32bit: pos.QuadPart = 22; break;
				case _64bit: pos.QuadPart = 38;
			}

			SEEK(pStream, pos, STREAM_SEEK_CUR);
			READ(pStream, sizeof(DWORD));
			DWORD NumOfDataDirs = min(cast<DWORD>(pData), IMAGE_NUMBEROF_DIRECTORY_ENTRIES);

			// Is this a .NET image?
			if (NumOfDataDirs < IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR + 1)
				m_bDotNet = false;
			else
			{
				// Then check CLR data directory
				pos.QuadPart = 112;
				SEEK(pStream, pos, STREAM_SEEK_CUR);
				READ(pStream, sizeof(DWORD));
				m_bDotNet = cast<DWORD>(pData) != 0;
			}

			m_bPreviousHandlerInitialized = false;	// Will change after successful initialization

			if (CLSID_PREVPEHANDLER == CLSID_NULL)
				break;

			// Let the previous property handler initialize
			// Get instance of class factory of previous handler
			CComPtr<IUnknown> interfaceUnknown;
			if (FAILED(CoCreateInstance(CLSID_PREVPEHANDLER, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&interfaceUnknown))))
				break;

			CComPtr<IInitializeWithFile> interfaceInitializeWithFile;
			if (FAILED(interfaceUnknown->QueryInterface(IID_PPV_ARGS(&interfaceInitializeWithFile))))
				break;

			// Caller initializer function in previous handler
			HRESULT hrPreviousHandlerInitialization = interfaceInitializeWithFile->Initialize(pszFilePath, grfMode);
			if (hrPreviousHandlerInitialization == STG_E_ACCESSDENIED)
				return hrPreviousHandlerInitialization;				// Seems like previous handler didn't like this 'grfMode', so we return the same value
			else if (FAILED(hrPreviousHandlerInitialization))
				break;

			// The following interfaces will be used in other functions
			if (FAILED(interfaceUnknown->QueryInterface(IID_PPV_ARGS(&m_interfacePropertyStore))))
				break;

			// We don't care if the following 'IPropertyStoreCapabilities' interface is not supported
			//	NOTE: When testing in Windows 7, the following function failed
			//	perhaps Windows 8 and future versions support this? Anyways, we do.
			// Implementing this interface allows us to properly disable property editing
			// by the user. With default property handler the comment section would appear
			// editable but when user tries to save the comment, Explorer wrongly gave an
			// access denied prompt. By implementing this, all this is avoided.
			interfaceUnknown->QueryInterface(IID_PPV_ARGS(&m_interfacePropertyStoreCapabilities));

			DWORD cPreviousHandlerProperties;
			if (FAILED(m_interfacePropertyStore->GetCount(&cPreviousHandlerProperties)))
				break;

			m_cSupportedProperties += cPreviousHandlerProperties;	// Add no. of properties that we added

			// Successfully initialized previous handler
			m_bPreviousHandlerInitialized = true;
		}
		
		break;

		case OBJ:
			m_cSupportedProperties = NUM_OF_ADDED_PROPERTIES;

			// Check machine type
			READ(pStream, sizeof(WORD));
			switch (cast<WORD>(pData))
			{
				case IMAGE_FILE_MACHINE_I386: m_ArchType = _32bit; break;
				case IMAGE_FILE_MACHINE_AMD64: m_ArchType = _64bit;	break;
				case IMAGE_FILE_MACHINE_IA64: m_ArchType = _I64; break;
				default: m_Format = Invalid; return S_OK;
			}

			break;
		
		case LIB:
			m_cSupportedProperties = NUM_OF_ADDED_PROPERTIES;

			// Check signature '!<arch>/n'
			READ(pStream, IMAGE_ARCHIVE_START_SIZE);
			if (string(cast<char *>(pData), IMAGE_ARCHIVE_START_SIZE) != IMAGE_ARCHIVE_START)
			{
				m_Format = Invalid;
				return S_OK;
			}

			// Skip first header + No. of symbols field
			//	and read file offset to either header for first symbol
			pos.QuadPart = IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR + sizeof(DWORD);
			SEEK(pStream, pos, STREAM_SEEK_CUR);
			READ(pStream, sizeof(DWORD));

			pos.QuadPart = _byteswap_ulong(cast<DWORD>(pData));	// Convert big endian to little endian
			SEEK(pStream, pos, STREAM_SEEK_SET);

			// Skip this header
			pos.QuadPart = IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR;
			SEEK(pStream, pos, STREAM_SEEK_CUR);

			// Check if this is a short version library used with static libs
			READ(pStream, sizeof(DWORD));
			if (cast<DWORD>(pData) == MAKELONG(IMAGE_FILE_MACHINE_UNKNOWN, 0xFFFF))
			{
				// Is a short version library
				// This is a Import header
				// Skip version field to read 'Machine' field
				pos.QuadPart = sizeof(WORD);
				SEEK(pStream, pos, STREAM_SEEK_CUR);
			}
			else
			{
				// Is a long version library
				// Rewind file pointer by size of 'DWORD'
				pos.QuadPart = -static_cast<LONGLONG>(sizeof(DWORD));
				SEEK(pStream, pos, STREAM_SEEK_CUR);
			}

			// Else it's a File header
			// Check machine type
			READ(pStream, sizeof(WORD));
			switch (cast<WORD>(pData))
			{
				case IMAGE_FILE_MACHINE_I386: m_ArchType = _32bit; break;
				case IMAGE_FILE_MACHINE_AMD64: m_ArchType = _64bit;	break;
				case IMAGE_FILE_MACHINE_IA64: m_ArchType = _I64; break;
				default: m_Format = Invalid; return S_OK;
			}

			break;
		
		default:
#ifdef _DEBUG
			throw exception("Unhandled file format");	// Execution shouldn't reach here
#else
			return E_UNEXPECTED;
#endif
	}

	return S_OK;
}