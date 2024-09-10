	void StripSignature(const std::wstring& path, int& retcode)
	{
		HANDLE file = CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file == INVALID_HANDLE_VALUE)
		{
			std::wcerr << "Failed to open file for writing." << std::endl;
			retcode = GetLastError();
			return;
		}

		bool enumerateFailed = false;
		DWORD count = 0;
		if (!ImageEnumerateCertificates(file, CERT_SECTION_TYPE_ANY, &count, NULL, 0))
		{
			std::wcerr << "Failed to enumerate certificates. " << GetLastError() << std::endl;
			enumerateFailed = true;
		}
		else
		{
			for (DWORD k = 0; k < count; ++k)
			{
				if (!ImageRemoveCertificate(file, k))
				{
					retcode = GetLastError();
					std::wcerr << "Failed to remove certificate: " << k << L". " << retcode << std::endl;
				}
			}
		}

		CloseHandle(file);

		if (enumerateFailed)
		{
			PEParser pe(path);
			pe.Open(true);
			if (pe.IsCorrupted())
				std::wcerr << L"Fixing signature directory entry." << std::endl;

			pe.EraseSignatureDirectory();
		}
	}