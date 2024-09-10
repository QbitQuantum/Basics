// Log format : "<LogType> <ThreadNo> <FileName> <Line> <ProcessName> : <Msg>"
void CStdDisplayer::doDisplay ( const CLog::TDisplayInfo& args, const char *message )
{
	bool needSpace = false;
	//stringstream ss;
	string str;

	if (args.LogType != CLog::LOG_NO)
	{
		//ss << logTypeToString(args.LogType);
		str += logTypeToString(args.LogType);
		needSpace = true;
	}

	// Write thread identifier
	if ( args.ThreadId != 0 )
	{
		//ss << setw(5) << args.ThreadId;
		if (needSpace) { str += " "; needSpace = false; }
#ifdef NL_OS_WINDOWS
		str += NLMISC::toString("%5x", args.ThreadId);
#else
		str += NLMISC::toString("%08x", args.ThreadId);
#endif
		needSpace = true;
	}

	if (args.FileName != NULL)
	{
		//if (needSpace) { ss << " "; needSpace = false; }
		if (needSpace) { str += " "; needSpace = false; }
		//ss << CFile::getFilename(args.FileName);
		str += CFile::getFilename(args.FileName);
		needSpace = true;
	}

	if (args.Line != -1)
	{
		//if (needSpace) { ss << " "; needSpace = false; }
		if (needSpace) { str += " "; needSpace = false; }
		//ss << args.Line;
		str += NLMISC::toString(args.Line);
		needSpace = true;
	}

	if (args.FuncName != NULL)
	{
		//if (needSpace) { ss << " "; needSpace = false; }
		if (needSpace) { str += " "; needSpace = false; }
		//ss << args.FuncName;
		str += args.FuncName;
		needSpace = true;
	}

	if (!args.ProcessName.empty())
	{
		//if (needSpace) { ss << " "; needSpace = false; }
		if (needSpace) { str += " "; needSpace = false; }
		//ss << args.ProcessName;
		str += args.ProcessName;
		needSpace = true;
	}

	//if (needSpace) { ss << " : "; needSpace = false; }
	if (needSpace) { str += " : "; needSpace = false; }

	//ss << message;
	str += message;

//	string s = ss.str();

	static bool consoleMode = true;

#if defined(NL_OS_WINDOWS)
	static bool consoleModeTest = false;
	if (!consoleModeTest)
	{
		HANDLE handle = CreateFile ("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
		consoleMode = handle != INVALID_HANDLE_VALUE;
		if (consoleMode)
			CloseHandle (handle);
		consoleModeTest = true;
	}
#endif // NL_OS_WINDOWS

	// Printf ?
	if (consoleMode)
	{
		// we don't use cout because sometimes, it crashs because cout isn't already init, printf doesn t crash.
		if (!str.empty())
			printf ("%s", str.c_str());

		if (!args.CallstackAndLog.empty())
			printf ("%s", args.CallstackAndLog.c_str());

		fflush(stdout);
	}

#ifdef NL_OS_WINDOWS
	// display the string in the debugger is the application is started with the debugger
	if (IsDebuggerPresent ())
	{
		//stringstream ss2;
		string str2;
		needSpace = false;

		if (args.FileName != NULL) str2 += args.FileName;

		if (args.Line != -1)
		{
			str2 += "(" + NLMISC::toString(args.Line) + ")";
			needSpace = true;
		}

		if (needSpace) { str2 += " : "; needSpace = false; }

		if (args.FuncName != NULL) str2 += string(args.FuncName) + " ";

		if (args.LogType != CLog::LOG_NO)
		{
			str2 += logTypeToString(args.LogType);
			needSpace = true;
		}

		// Write thread identifier
		if ( args.ThreadId != 0 )
		{
			str2 += NLMISC::toString("%5x: ", args.ThreadId);
		}

		str2 += message;

		const sint maxOutString = 2*1024;

		if(str2.size() < maxOutString)
		{
			//////////////////////////////////////////////////////////////////
			// WARNING: READ THIS !!!!!!!!!!!!!!!! ///////////////////////////
			// If at the release time, it freezes here, it's a microsoft bug:
			// http://support.microsoft.com/support/kb/articles/q173/2/60.asp
			OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8(str2).c_str());
		}
		else
		{
			/*OutputDebugString(ss2.str().c_str());
			OutputDebugString("\n\t\t\t");
			OutputDebugString("message end: ");
			OutputDebugString(&message[strlen(message) - 1024]);
			OutputDebugString("\n");*/

			sint count = 0;
			uint n = (uint)strlen(message);
			std::string s(&str2.c_str()[0], (str2.size() - n));
			OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8(s).c_str());

			for(;;)
			{

				if((n - count) < maxOutString )
				{
					s = std::string(&message[count], (n - count));
					OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8(s).c_str());
					OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8("\n").c_str());
					break;
				}
				else
				{
					s = std::string(&message[count] , count + maxOutString);
					OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8(s).c_str());
					OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8("\n\t\t\t").c_str());
					count += maxOutString;
				}
			}
		}

		// OutputDebugString is a big shit, we can't display big string in one time, we need to split
		uint32 pos = 0;
		string splited;
		for(;;)
		{
			if (pos+1000 < args.CallstackAndLog.size ())
			{
				splited = args.CallstackAndLog.substr (pos, 1000);
				OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8(splited).c_str());
				pos += 1000;
			}
			else
			{
				splited = args.CallstackAndLog.substr (pos);
				OutputDebugStringW((LPCWSTR)ucstring::makeFromUtf8(splited).c_str());
				break;
			}
		}
	}
#endif
}