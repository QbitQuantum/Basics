void GetVersionInfo(const char * name, VersionInfo * pInfo)
{
	HMODULE hVersion = LoadLibraryA("version.dll");
	memset(pInfo, 0, sizeof(VersionInfo));
	if (NULL != hVersion)
	{
		pfnGetFileVersionInfoA GetFileVersionInfoA = (pfnGetFileVersionInfoA) GetProcAddress(hVersion, "GetFileVersionInfoA");
		pfnGetFileVersionInfoSizeA GetFileVersionInfoSizeA = (pfnGetFileVersionInfoSizeA) GetProcAddress(hVersion, "GetFileVersionInfoSizeA");
		pfnVerQueryValueA VerQueryValueA = (pfnVerQueryValueA) GetProcAddress(hVersion, "VerQueryValueA");
		if (NULL != GetFileVersionInfoA && NULL != GetFileVersionInfoSizeA && NULL != VerQueryValueA)
		{
			DWORD dummy = 0;
			DWORD size = GetFileVersionInfoSize(name, &dummy);
			if (size > 0 && size <= 8192)
			{
				char block[8192];
				if (GetFileVersionInfo(name, dummy, size, block))
				{
					struct LANGANDCODEPAGE
					{
						WORD language;
						WORD codepage;
					}
					* pTranslate;
					UINT blocksize;
					if (VerQueryValueA(block, "\\VarFileInfo\\Translation", (LPVOID*)&pTranslate, &blocksize))
					{
						uint32_t i;
						for (i = 0; i < blocksize / sizeof(struct LANGANDCODEPAGE); ++i)
						{
							UINT dummy;
							char * value = NULL;
							char subblock[50];
							char * tokens[] =
							{
								"Comments",
								"CompanyName",
								"FileDescription",
								"FileVersion",
								"InternalName",
								"LegalCopyright",
								"LegalTrademarks",
								"OriginalFilename",
								"ProductName",
								"ProductVersion",
								"PrivateBuild",
								"SpecialBuild"
							};
							size_t j;
							for (j = 0; j < sizeof(tokens) / sizeof(tokens[0]); ++j)
							{
								ConsoleIOFormat(subblock, 50, "\\StringFileInfo\\%04x%04x\\%s", pTranslate[i].language, pTranslate[i].codepage, tokens[j]);
								if (VerQueryValueA(block, subblock, &value, &dummy))
								{
									xstrcat((char*)pInfo + kMaxVersionString * j, kMaxVersionString, value);
								}
							}
						}
					}
				}
			}
		}
		FreeLibrary(hVersion);
	}
}