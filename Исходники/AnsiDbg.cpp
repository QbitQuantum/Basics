DWORD WINAPI ProcessSrvThread(LPVOID lpParameter)
{
	LPCTSTR asName = (LPCTSTR)lpParameter;
	HANDLE hPipeIn;
	TCHAR szName[MAX_PATH] = _T("\\\\.\\pipe\\");
	_tcscat(szName, asName);

	BOOL b; DWORD nRead, nWrite; char c;

	hPipeIn = CreateNamedPipe(szName, PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE, 1, 80, 80, 0, NULL);
	if (!hPipeIn || hPipeIn == INVALID_HANDLE_VALUE)
	{
		return PrintOut("\n!!! CreateNamedPipe failed, code=%u !!!\n");
	}

	char sInfo[300] = "";
	wsprintfA(sInfo, "Server started, PID=%u\nWaiting for client '", GetCurrentProcessId());
#ifdef _UNICODE
	WideCharToMultiByte(CP_OEMCP, 0, asName, -1, sInfo+lstrlenA(sInfo), 200, 0, 0);
#else
	lstrcat(sInfo, asName);
#endif
	lstrcatA(sInfo, "'...\n");
	PrintOut(sInfo);
	b = ConnectNamedPipe(hPipeIn, NULL);
	if (!b)
	{
		return PrintOut("\n!!! ConnectNamedPipe failed, code=%u !!!\n");
	}
	PrintOut("Connected!\n");

	while (true)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		b = ReadFile(hPipeIn, &c, 1, &nRead, NULL);
		if (b && nRead)
		{
			EnterCriticalSection(&cs);
			switch (c)
			{
			case 1:
			{
				Sleep(200);
				HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
				INPUT_RECORD ir = {KEY_EVENT};
				ir.Event.KeyEvent.bKeyDown = TRUE;
				ir.Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
				ir.Event.KeyEvent.uChar.AsciiChar = '\r';
				b = WriteConsoleInputA(hIn, &ir, 1, &nWrite);
				nRead = GetLastError();
				if (!b && FindMinTTY())
				{
					PostMessage(hMinTTY, WM_CHAR, '\r', 0);
				}
				b = TRUE; nRead = nWrite;
				break;
			}
			case 2:
			{
				int width = 80, height = 25;
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				if (GetConsoleScreenBufferInfo(hOut, &csbi))
				{
					width = max(csbi.dwSize.X,20);
					height = max(25,(csbi.dwSize.Y-csbi.dwCursorPosition.Y-1));
				}
				char* szText = (char*)malloc(width+20);
				for (int i = 1; i <= height; i++)
				{
					sprintf(szText, "Line %-4u ", i);
					char* psz = szText + strlen(szText);
					for (int j = 1; (psz - szText) < width; j++)
					{
						sprintf(psz, "Word %u ", j);
						psz += strlen(psz);
					}
					psz = szText+width-1;
					*(psz++) = L'\r'; *(psz++) = L'\n'; *psz = 0;
					WriteFile(hOut, szText, psz - szText, &nWrite, NULL);
				}
				b = TRUE; nRead = nWrite;
				break;
			}
			default:
				b = WriteFile(hOut, &c, nRead, &nWrite, NULL);
			}
			LeaveCriticalSection(&cs);
			if (!b || nWrite != nRead)
			{
				PrintOut("\n!!! WriteFile(StdOut) failed, code=%u !!!\n");
				break;
			}
		}
		else
		{
			nRead = GetLastError();
			PrintOut("\n!!! Pipe reading error, code=%u !!!\n");
			break;
		}
	}

	// CygWin/mintty hack to exit process
	TerminateProcess(GetCurrentProcess(), 1);
	return 0;
}