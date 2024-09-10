//Print errors to log file
bool __fastcall PrintError(
	_In_ const size_t ErrorType, 
	_In_ const wchar_t *Message, 
	_In_opt_ const SSIZE_T ErrorCode, 
	_In_opt_ const wchar_t *FileName, 
	_In_opt_ const size_t Line)
{
//Print Error: Enable/Disable, parameter check, message check and file name check
	if (!Parameter.PrintError || //PrintError 
		Message == nullptr || CheckEmptyBuffer(Message, wcsnlen_s(Message, ORIGINAL_PACKET_MAXSIZE) * sizeof(wchar_t)) || 
		FileName != nullptr && CheckEmptyBuffer(FileName, wcsnlen_s(FileName, ORIGINAL_PACKET_MAXSIZE) * sizeof(wchar_t)))
			return false;

//Convert file name.
	std::wstring FileNameString, ErrorMessage;
	if (FileName != nullptr)
	{
		FileNameString.append(L" in ");

	//Add line number.
		if (Line > 0)
			FileNameString.append(L"line %d of ");

	//Delete double backslash.
		FileNameString.append(FileName);
		while (FileNameString.find(L"\\\\") != std::wstring::npos)
			FileNameString.erase(FileNameString.find(L"\\\\"), wcslen(L"\\"));
	}

//Add log error type.
	switch (ErrorType)
	{
	//Message Notice
		case LOG_MESSAGE_NOTICE:
		{
			ErrorMessage.append(L"Notice: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//System Error
	//About System Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx.
		case LOG_ERROR_SYSTEM:
		{
			ErrorMessage.append(L"System Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
		#if defined(PLATFORM_WIN)
			else if (ErrorCode == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
				ErrorMessage.append(L", ERROR_FAILED_SERVICE_CONTROLLER_CONNECT(The service process could not connect to the service controller).\n");
		#endif
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//Parameter Error
		case LOG_ERROR_PARAMETER:
		{
			ErrorMessage.append(L"Parameter Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//IPFilter Error
	//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
		case LOG_ERROR_IPFILTER:
		{
			ErrorMessage.append(L"IPFilter Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//Hosts Error
	//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
		case LOG_ERROR_HOSTS:
		{
			ErrorMessage.append(L"Hosts Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//Network Error
	//About Windows Sockets Error Codes, see http://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx.
		case LOG_ERROR_NETWORK:
		{
			ErrorMessage.append(L"Network Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
		#if defined(PLATFORM_WIN)
			else if (ErrorCode == WSAENETUNREACH || //Block error messages when getting Network Unreachable error.
				ErrorCode == WSAEHOSTUNREACH) //Block error messages when getting Host Unreachable error.
					return true;
		#endif
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//WinPcap Error
	#if defined(ENABLE_PCAP)
		case LOG_ERROR_PCAP:
		{
			ErrorMessage.append(L"Pcap Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

/* There are no any error codes to be reported in LOG_ERROR_PCAP.
		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
*/
			ErrorMessage.append(L"\n");
		}break;
	#endif
	//DNSCurve Error
	#if defined(ENABLE_LIBSODIUM)
		case LOG_ERROR_DNSCURVE:
		{
			ErrorMessage.append(L"DNSCurve Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	#endif
	//SOCKS Error
		case LOG_ERROR_SOCKS:
		{
			ErrorMessage.append(L"SOCKS Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
	//HTTP Error
		case LOG_ERROR_HTTP:
		{
			ErrorMessage.append(L"HTTP Error: ");
			ErrorMessage.append(Message);

		//Copy file name and its line number to error log.
			if (!FileNameString.empty())
				ErrorMessage.append(FileNameString);

		//Add error code.
			if (ErrorCode == 0)
				ErrorMessage.append(L".\n");
			else 
				ErrorMessage.append(L", error code is %d.\n");
		}break;
		default:
		{
			return false;
		}
	}

//Print error log.
	return PrintScreenAndWriteFile(ErrorMessage, ErrorCode, Line);
}