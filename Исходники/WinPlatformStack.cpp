	void PlatformStack::ProgramAddressToSymbolInfo(uint64 address, SymbolInfo& oSymbolInfo)
	{
		InitSysStack();

		oSymbolInfo.Address = address;

		uint32 lastError = 0;
		HANDLE processHandle = GetCurrentProcess();

		ansichar symbolBuffer[sizeof(IMAGEHLP_SYMBOL64) + SymbolInfo::MAX_NAME_LENGHT] = { 0 };
		IMAGEHLP_SYMBOL64* symbol = (IMAGEHLP_SYMBOL64*)symbolBuffer;
		symbol->SizeOfStruct = sizeof(symbolBuffer);
		symbol->MaxNameLength = SymbolInfo::MAX_NAME_LENGHT;

		if (SymGetSymFromAddr64(processHandle, address, nullptr, symbol))
		{
			int32 offset = 0;
			while (symbol->Name[offset] < 32 || symbol->Name[offset] > 127)
			{
				offset++;
			}

			strncpy(oSymbolInfo.FunctionName, symbol->Name + offset, SymbolInfo::MAX_NAME_LENGHT);
			strncat(oSymbolInfo.FunctionName, "()", SymbolInfo::MAX_NAME_LENGHT);
		}
		else
		{
			lastError = GetLastError();
		}

		IMAGEHLP_LINE64	imageHelpLine = { 0 };
		imageHelpLine.SizeOfStruct = sizeof(imageHelpLine);
		if (SymGetLineFromAddr64(processHandle, address, (::DWORD *)&oSymbolInfo.SymbolDisplacement, &imageHelpLine))
		{
			strncpy(oSymbolInfo.FileName, imageHelpLine.FileName, SymbolInfo::MAX_NAME_LENGHT);
			oSymbolInfo.LineNumber = imageHelpLine.LineNumber;
		}
		else
		{
			lastError = GetLastError();
		}

		IMAGEHLP_MODULE64 imageHelpModule = { 0 };
		imageHelpModule.SizeOfStruct = sizeof(imageHelpModule);
		if (SymGetModuleInfo64(processHandle, address, &imageHelpModule))
		{
			strncpy(oSymbolInfo.ModuleName, imageHelpModule.ImageName, SymbolInfo::MAX_NAME_LENGHT);
		}
		else
		{
			lastError = GetLastError();
		}
	}