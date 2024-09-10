void CommandHandler::DoWriteKeyValueBang(std::vector<std::wstring>& args, MeterWindow* skin)
{
	if (args.size() == 3 && skin)
	{
		// Add the skin file path to the args
		args.push_back(skin->GetFilePath());
	}
	else if (args.size() < 4)
	{
		LogErrorF(skin, L"!WriteKeyValue: Invalid parameters");
		return;
	}

	std::wstring& strIniFile = args[3];
	if (skin)
	{
		skin->MakePathAbsolute(strIniFile);
	}

	const WCHAR* iniFile = strIniFile.c_str();

	if (strIniFile.find(L"..\\") != std::wstring::npos || strIniFile.find(L"../") != std::wstring::npos)
	{
		LogErrorF(skin, L"!WriteKeyValue: Illegal path: %s", iniFile);
		return;
	}

	if (_wcsnicmp(iniFile, GetRainmeter().m_SkinPath.c_str(), GetRainmeter().m_SkinPath.size()) != 0 &&
		_wcsnicmp(iniFile, GetRainmeter().m_SettingsPath.c_str(), GetRainmeter().m_SettingsPath.size()) != 0)
	{
		LogErrorF(skin, L"!WriteKeyValue: Illegal path: %s", iniFile);
		return;
	}

	// Verify whether the file exists.
	if (_waccess(iniFile, 0) == -1)
	{
		LogErrorF(skin, L"!WriteKeyValue: File not found: %s", iniFile);
		return;
	}

	// Verify whether the file is read-only.
	DWORD attr = GetFileAttributes(iniFile);
	if (attr == -1 || (attr & FILE_ATTRIBUTE_READONLY))
	{
		LogWarningF(skin, L"!WriteKeyValue: File is read-only: %s", iniFile);
		return;
	}

	// Avoid "IniFileMapping"
	System::UpdateIniFileMappingList();
	std::wstring strIniWrite = System::GetTemporaryFile(strIniFile);
	if (strIniWrite.size() == 1 && strIniWrite[0] == L'?')  // error occurred
	{
		return;
	}

	bool temporary = !strIniWrite.empty();

	if (temporary)
	{
		if (GetRainmeter().GetDebug())
		{
			LogDebugF(skin, L"!WriteKeyValue: Writing to: %s (Temp: %s)", iniFile, strIniWrite.c_str());
		}
	}
	else
	{
		if (GetRainmeter().GetDebug())
		{
			LogDebugF(skin, L"!WriteKeyValue: Writing to: %s", iniFile);
		}
		strIniWrite = strIniFile;
	}

	const WCHAR* iniWrite = strIniWrite.c_str();
	const WCHAR* section = args[0].c_str();
	const WCHAR* key = args[1].c_str();
	const std::wstring& strValue = args[2];

	bool formula = false;
	BOOL write = 0;

	if (skin)
	{
		double value;
		formula = skin->GetParser().ParseFormula(strValue, &value); 
		if (formula)
		{
			WCHAR buffer[256];
			int len = _snwprintf_s(buffer, _TRUNCATE, L"%.5f", value);
			Measure::RemoveTrailingZero(buffer, len);

			write = WritePrivateProfileString(section, key, buffer, iniWrite);
		}
	}

	if (!formula)
	{
		write = WritePrivateProfileString(section, key, strValue.c_str(), iniWrite);
	}

	if (temporary)
	{
		if (write != 0)
		{
			WritePrivateProfileString(nullptr, nullptr, nullptr, iniWrite);  // FLUSH

			// Copy the file back.
			if (!System::CopyFiles(strIniWrite, strIniFile))
			{
				LogErrorF(skin, L"!WriteKeyValue: Failed to copy temporary file to original filepath: %s (Temp: %s)", iniFile, iniWrite);
			}
		}
		else  // failed
		{
			LogErrorF(skin, L"!WriteKeyValue: Failed to write to: %s (Temp: %s)", iniFile, iniWrite);
		}

		// Remove the temporary file.
		System::RemoveFile(strIniWrite);
	}
	else
	{
		if (write == 0)  // failed
		{
			LogErrorF(skin, L"!WriteKeyValue: Failed to write to: %s", iniFile);
		}
	}
}