bool IntegrityCheckModule(const char *moduleFilename, const byte *expectedModuleMac, SecByteBlock *pActualMac, unsigned long *pMacFileLocation)
{
	std::auto_ptr<MessageAuthenticationCode> mac(NewIntegrityCheckingMAC());
	unsigned int macSize = mac->DigestSize();

	SecByteBlock tempMac;
	SecByteBlock &actualMac = pActualMac ? *pActualMac : tempMac;
	actualMac.resize(macSize);

	unsigned long tempLocation;
	unsigned long &macFileLocation = pMacFileLocation ? *pMacFileLocation : tempLocation;
	macFileLocation = 0;

	MeterFilter verifier(new HashFilter(*mac, new ArraySink(actualMac, actualMac.size())));
//	MeterFilter verifier(new FileSink("c:\\dt.tmp"));
	std::ifstream moduleStream;

#ifdef CRYPTOPP_WIN32_AVAILABLE
	HMODULE h;
	{
	char moduleFilenameBuf[MAX_PATH] = "";
	if (moduleFilename == NULL)
	{
#if (_MSC_VER >= 1400 && !defined(_STLPORT_VERSION))	// ifstream doesn't support wide filename on other compilers
		wchar_t wideModuleFilename[MAX_PATH];
		if (GetModuleFileNameW(s_hModule, wideModuleFilename, MAX_PATH) > 0)
		{
			moduleStream.open(wideModuleFilename, std::ios::in | std::ios::binary);
			h = GetModuleHandleW(wideModuleFilename);
		}
		else
#endif
		{
			GetModuleFileNameA(s_hModule, moduleFilenameBuf, MAX_PATH);
			moduleFilename = moduleFilenameBuf;
		}
	}
#endif
	if (moduleFilename != NULL)
	{
			moduleStream.open(moduleFilename, std::ios::in | std::ios::binary);
#ifdef CRYPTOPP_WIN32_AVAILABLE
			h = GetModuleHandleA(moduleFilename);
			moduleFilename = NULL;
	}
#endif
	}

	if (!moduleStream)
	{
#ifdef CRYPTOPP_WIN32_AVAILABLE
		OutputDebugString("Crypto++ DLL integrity check failed. Cannot open file for reading.");
#endif
		return false;
	}
	FileStore file(moduleStream);

#ifdef CRYPTOPP_WIN32_AVAILABLE
	// try to hash from memory first
	const byte *memBase = (const byte *)h;
	const IMAGE_DOS_HEADER *ph = (IMAGE_DOS_HEADER *)memBase;
	const IMAGE_NT_HEADERS *phnt = (IMAGE_NT_HEADERS *)(memBase + ph->e_lfanew);
	const IMAGE_SECTION_HEADER *phs = IMAGE_FIRST_SECTION(phnt);
	DWORD nSections = phnt->FileHeader.NumberOfSections;
	size_t currentFilePos = 0;

	size_t checksumPos = (byte *)&phnt->OptionalHeader.CheckSum - memBase;
	size_t checksumSize = sizeof(phnt->OptionalHeader.CheckSum);
	size_t certificateTableDirectoryPos = (byte *)&phnt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY] - memBase;
	size_t certificateTableDirectorySize = sizeof(phnt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY]);
	size_t certificateTablePos = phnt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress;
	size_t certificateTableSize = phnt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size;

	verifier.AddRangeToSkip(0, checksumPos, checksumSize);
	verifier.AddRangeToSkip(0, certificateTableDirectoryPos, certificateTableDirectorySize);
	verifier.AddRangeToSkip(0, certificateTablePos, certificateTableSize);

	while (nSections--)
	{
		switch (phs->Characteristics)
		{
		default:
			break;
		case IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ:
		case IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ:
			unsigned int sectionSize = STDMIN(phs->SizeOfRawData, phs->Misc.VirtualSize);
			const byte *sectionMemStart = memBase + phs->VirtualAddress;
			unsigned int sectionFileStart = phs->PointerToRawData;
			size_t subSectionStart = 0, nextSubSectionStart;

			do
			{
				const byte *subSectionMemStart = sectionMemStart + subSectionStart;
				size_t subSectionFileStart = sectionFileStart + subSectionStart;
				size_t subSectionSize = sectionSize - subSectionStart;
				nextSubSectionStart = 0;

				unsigned int entriesToReadFromDisk[] = {IMAGE_DIRECTORY_ENTRY_IMPORT, IMAGE_DIRECTORY_ENTRY_IAT};
				for (unsigned int i=0; i<sizeof(entriesToReadFromDisk)/sizeof(entriesToReadFromDisk[0]); i++)
				{
					const IMAGE_DATA_DIRECTORY &entry = phnt->OptionalHeader.DataDirectory[entriesToReadFromDisk[i]];
					const byte *entryMemStart = memBase + entry.VirtualAddress;
					if (subSectionMemStart <= entryMemStart && entryMemStart < subSectionMemStart + subSectionSize)
					{
						subSectionSize = entryMemStart - subSectionMemStart;
						nextSubSectionStart = entryMemStart - sectionMemStart + entry.Size;
					}
				}

#if defined(_MSC_VER) && _MSC_VER >= 1400
				// first byte of _CRT_DEBUGGER_HOOK gets modified in memory by the debugger invisibly, so read it from file
				if (IsDebuggerPresent())
				{
					if (subSectionMemStart <= (byte *)&_CRT_DEBUGGER_HOOK && (byte *)&_CRT_DEBUGGER_HOOK < subSectionMemStart + subSectionSize)
					{
						subSectionSize = (byte *)&_CRT_DEBUGGER_HOOK - subSectionMemStart;
						nextSubSectionStart = (byte *)&_CRT_DEBUGGER_HOOK - sectionMemStart + 1;
					}
				}
#endif

				if (subSectionMemStart <= expectedModuleMac && expectedModuleMac < subSectionMemStart + subSectionSize)
				{
					// found stored MAC
					macFileLocation = (unsigned long)(subSectionFileStart + (expectedModuleMac - subSectionMemStart));
					verifier.AddRangeToSkip(0, macFileLocation, macSize);
				}

				file.TransferTo(verifier, subSectionFileStart - currentFilePos);
				verifier.Put(subSectionMemStart, subSectionSize);
				file.Skip(subSectionSize);
				currentFilePos = subSectionFileStart + subSectionSize;
				subSectionStart = nextSubSectionStart;
			} while (nextSubSectionStart != 0);
		}
		phs++;
	}
#endif
	file.TransferAllTo(verifier);

#ifdef CRYPTOPP_WIN32_AVAILABLE
	// if that fails (could be caused by debug breakpoints or DLL base relocation modifying image in memory),
	// hash from disk instead
	if (memcmp(expectedModuleMac, actualMac, macSize) != 0)
	{
		OutputDebugString("In memory integrity check failed. This may be caused by debug breakpoints or DLL relocation.\n");
		moduleStream.clear();
		moduleStream.seekg(0);
		verifier.Initialize(MakeParameters(Name::OutputBuffer(), ByteArrayParameter(actualMac, (unsigned int)actualMac.size())));
//		verifier.Initialize(MakeParameters(Name::OutputFileName(), (const char *)"c:\\dt2.tmp"));
		verifier.AddRangeToSkip(0, checksumPos, checksumSize);
		verifier.AddRangeToSkip(0, certificateTableDirectoryPos, certificateTableDirectorySize);
		verifier.AddRangeToSkip(0, certificateTablePos, certificateTableSize);
		verifier.AddRangeToSkip(0, macFileLocation, macSize);
		FileStore(moduleStream).TransferAllTo(verifier);
	}
#endif

	if (memcmp(expectedModuleMac, actualMac, macSize) == 0)
		return true;

#ifdef CRYPTOPP_WIN32_AVAILABLE
	std::string hexMac;
	HexEncoder(new StringSink(hexMac)).PutMessageEnd(actualMac, actualMac.size());
	OutputDebugString((("Crypto++ DLL integrity check failed. Actual MAC is: " + hexMac) + "\n").c_str());
#endif
	return false;
}