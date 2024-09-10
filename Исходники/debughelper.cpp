	std::wstring DebugHelper::DumpModules(uint32 processId) const {
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
		if (hSnapshot == INVALID_HANDLE_VALUE)
			throw std::runtime_error("Could not create module snapshot!");

		std::wostringstream strmModules;
		MODULEENTRY32W moduleEntry = {0};
		moduleEntry.dwSize = sizeof(moduleEntry);

		if (Module32FirstW(hSnapshot, &moduleEntry) != FALSE) {
			do if (moduleEntry.th32ProcessID == processId) {
				strmModules << L"  0x" << std::hex << std::uppercase
							<< reinterpret_cast<void*>(moduleEntry.modBaseAddr) << L": "
							<< (moduleEntry.szModule != nullptr ? moduleEntry.szModule : L"<null>");

				if (moduleEntry.szExePath != nullptr) {
					DWORD dwVersionInfoHandle = 0;
					DWORD dwVersionInfoSize = GetFileVersionInfoSizeW(moduleEntry.szExePath, &dwVersionInfoHandle);

					UINT fileInfoSize = 0;
					VS_FIXEDFILEINFO *pFileInfo = nullptr;
					Utils::ByteBuffer versionInfoBuffer(dwVersionInfoSize);

					if (dwVersionInfoSize != 0 &&

						GetFileVersionInfoW(moduleEntry.szExePath, dwVersionInfoHandle,
							dwVersionInfoSize, versionInfoBuffer.data()) != FALSE &&

						VerQueryValueW(versionInfoBuffer.data(), L"\\",
							reinterpret_cast<LPVOID*>(&pFileInfo), &fileInfoSize) != FALSE &&

						fileInfoSize >= sizeof(VS_FIXEDFILEINFO))
					{
						// Output file version string...
						strmModules << L" (" << std::dec
									<< HIWORD(pFileInfo->dwFileVersionMS) << L'.'
									<< LOWORD(pFileInfo->dwFileVersionMS) << L'.'
									<< HIWORD(pFileInfo->dwFileVersionLS) << L'.'
									<< LOWORD(pFileInfo->dwFileVersionLS) << L')';
					}
				}

				strmModules << L"\r\n";
			}
			while (Module32NextW(hSnapshot, &moduleEntry) != FALSE);
		}

		CloseHandle(hSnapshot);
		return strmModules.str();
	}