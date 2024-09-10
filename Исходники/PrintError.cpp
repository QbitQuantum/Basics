//Print errors to log file
size_t __fastcall PrintError(const size_t Type, const PWSTR Message, const SSIZE_T Code, const PWSTR FileName, const size_t Line)
{
//Print Errors: ON/OFF.
	if (!Parameter.PrintError || Message == nullptr)
		return FALSE;

//Get current date&time.
	tm Time = {0};
	time_t tTime = 0;
	time(&tTime);
	localtime_s(&Time, &tTime);
/*
//Windows API
	SYSTEMTIME Time = {0};
	GetLocalTime(&Time);
	fwprintf_s(Output, L"%u%u/%u %u:%u:%u -> %s.\n", Time.wYear, Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond, pBuffer); //Windows API

//Convert to ASCII.
	char TimeBuf[ADDR_STRING_MAXSIZE] = {0};
	asctime_s(TimeBuf, &Time);
	fwprintf_s(Output, L"%s -> %s.\n", TimeBuf, pBuffer);
*/

	FILE *Output = nullptr;
	_wfopen_s(&Output, ErrorLogPath.c_str(), L"a,ccs=UTF-8");
	if (Output != nullptr)
	{
	// Error Type
	// 01: System Error
	// 02: Parameter Error
	// 03: IPFilter Error
	// 04: Hosts Error
	// 05: Winsock Error
	// 06: WinPcap Error
	// 07: DNSCurve Error
		switch (Type)
		{
		//System Error
			case SYSTEM_ERROR:
			{
				if (Code == NULL)
				{
					fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> System Error: %ls.\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
				}
				else {
				//About System Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx.
					if (Code == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
						fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> System Error: %ls, ERROR_FAILED_SERVICE_CONTROLLER_CONNECT(The service process could not connect to the service controller).\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
					else 
						fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> System Error: %ls, error code is %d.\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message, (int)Code);
				}
			}break;
		//Parameter Error
			case PARAMETER_ERROR:
			{
				fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> Parameter Error: %ls", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
				if (FileName != nullptr && Line != NULL)
				{
				//Delete double backslash.
					std::wstring sFileName(FileName);
					while (sFileName.find(L"\\\\") != std::wstring::npos)
						sFileName.erase((size_t)sFileName.find(L"\\\\"), 1U);

				//Write to file
					fwprintf_s(Output, L" in line %d of %ls", (int)Line, sFileName.c_str());
				}

			//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
				if (Code != NULL)
					fwprintf_s(Output, L", error code is %d", (int)Code);

				fwprintf_s(Output, L".\n");
			}break;
		//IPFilter Error
			case IPFILTER_ERROR:
			{
				fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> IPFilter Error: %ls", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
				if (FileName != nullptr && Line != NULL)
				{
				//Delete double backslash.
					std::wstring sFileName(FileName);
					while (sFileName.find(L"\\\\") != std::wstring::npos)
						sFileName.erase((size_t)sFileName.find(L"\\\\"), 1U);

				//Write to file
					fwprintf_s(Output, L" in line %d of %ls", (int)Line, sFileName.c_str());
				}

			//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
				if (Code != NULL)
					fwprintf_s(Output, L", error code is %d", (int)Code);

				fwprintf_s(Output, L".\n");
			}break;
		//Hosts Error
			case HOSTS_ERROR:
			{
				fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> Hosts Error: %ls", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
				if (FileName != nullptr && Line != NULL)
				{
				//Delete double backslash.
					std::wstring sFileName(FileName);
					while (sFileName.find(L"\\\\") != std::wstring::npos)
						sFileName.erase((size_t)sFileName.find(L"\\\\"), 1U);

				//Write to file
					fwprintf_s(Output, L" in line %d of %ls", (int)Line, sFileName.c_str());
				}

			//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
				if (Code != NULL)
					fwprintf_s(Output, L", error code is %d", (int)Code);

				fwprintf_s(Output, L".\n");
			}break;
		//Winsock Error
		//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
			case WINSOCK_ERROR:
			{
				if (Code == NULL)
					fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> Winsock Error: %ls.\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
				else 
					fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> Winsock Error: %ls, error code is %d.\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message, (int)Code);
			}break;
		//WinPcap Error
			case WINPCAP_ERROR:
			{
				fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> WinPcap Error: %ls.\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
			}break;
		//DNSCurve Error
			case DNSCURVE_ERROR:
			{
				fwprintf_s(Output, L"%d-%02d-%02d %02d:%02d:%02d -> DNSCurve Error: %ls.\n", Time.tm_year + 1900, Time.tm_mon + 1, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec, Message);
			}break;
			default:
			{
				fclose(Output);
				return EXIT_FAILURE;
			}
		}

		fclose(Output);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}