static void CommandLineKey(int id, WPARAM wParam, int keytype)
{
	TCHAR code = (TCHAR)wParam;
	int len = (int)wcslen(commandLine);
	if (keytype == KEYCHAR) {
		if (!commandLineFocus && code == L':') {
			CreateCaret(g_hWnd, (HBITMAP)NULL, 1, FONTSIZE_CMD);
			commandLineFocus = 1;
			commandLine[commandLinePos++] = L':';
			commandLine[commandLinePos] = L'\0';
			CommandLineSetpos();
			ShowCaret(g_hWnd);
		}
		else if (commandLineFocus) {
			if (code == L'\r' || code == VK_ESCAPE) {
				if(code == L'\r' && LoaderRun(commandLine + 1))
					ErrorPrintf(L"CommandLineError: Cannot parse the command");
				commandLine[0] = L'\0';
				commandLinePos = 0;
				commandLineFocus = 0;
				HideCaret(g_hWnd);
				DestroyCaret();
				memset(KeyboardIsDown, 0, sizeof(KeyboardIsDown));
			}
			if (code < L' ' || len == MAX_COMMANDLINEBUFFER) return;
			MoveMemory(commandLine + commandLinePos + 1, commandLine + commandLinePos, (len - commandLinePos + 1) * sizeof(TCHAR));
			commandLine[commandLinePos++] = code;
			CommandLineSetpos();
		}
	}
	else if (keytype == KEYDOWN && commandLineFocus) {
		switch (code)
		{
		case VK_LEFT:
			if (commandLinePos > 1) --commandLinePos;
			CommandLineSetpos();
			break;
		case VK_RIGHT:
			if (commandLinePos < len) ++commandLinePos;
			CommandLineSetpos();
			break;
		case VK_HOME:
			commandLinePos = 1;
			break;
		case VK_END:
			commandLinePos = len;
			break;
		case VK_BACK:
			if (commandLinePos > 1) {
				MoveMemory(commandLine + commandLinePos - 1, commandLine + commandLinePos, (len - commandLinePos + 1) * sizeof(TCHAR));
				commandLinePos--;
			}
			CommandLineSetpos();
			break;
		}
	}
}