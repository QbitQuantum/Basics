BOOL OnPromptBsDeleteWord(bool bForce, bool bBashMargin)
{
	HANDLE hConIn = NULL;
	if (!IsPromptActionAllowed(bForce, bBashMargin, &hConIn))
	{
		BsDelWordMsg(L"Skipped due to !IsPromptActionAllowed!");
		return FALSE;
	}

	int iBSCount = 0;
	BOOL lbWrite = FALSE;
	DWORD dwLastError = 0;

	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	if (GetConsoleScreenBufferInfo(hConOut, &csbi) && csbi.dwSize.X && csbi.dwSize.Y)
	{
		if (csbi.dwCursorPosition.X == 0)
		{
			iBSCount = 1;
		}
		else
		{
			bool bDBCS = false;
			DWORD nRead = 0;
			BOOL bReadOk = FALSE;

			// Если в консоли выбрана DBCS кодировка - там все не просто
			DWORD nCP = GetConsoleOutputCP();
			if (nCP && nCP != CP_UTF7 && nCP != CP_UTF8 && nCP != 1200 && nCP != 1201)
			{
				CPINFO cp = {};
				if (GetCPInfo(nCP, &cp) && (cp.MaxCharSize > 1))
				{
					bDBCS = true;
				}
			}

			#ifdef _DEBUG
			wchar_t szDbg[120];
			_wsprintf(szDbg, SKIPCOUNT(szDbg) L"CP=%u bDBCS=%u IsDbcs=%u X=%i", nCP, bDBCS, IsDbcs(), csbi.dwCursorPosition.X);
			BsDelWordMsg(szDbg);
			#endif

			int xPos = csbi.dwCursorPosition.X;
			COORD cr = {0, csbi.dwCursorPosition.Y};
			if ((xPos == 0) && (csbi.dwCursorPosition.Y > 0))
			{
				cr.Y--;
				xPos = csbi.dwSize.X;
			}
			COORD cursorFix = {xPos, cr.Y};

			wchar_t* pwszLine = (wchar_t*)malloc((csbi.dwSize.X+1)*sizeof(*pwszLine));


			if (pwszLine)
			{
				pwszLine[csbi.dwSize.X] = 0;

				// Считать строку
				if (bDBCS)
				{
					CHAR_INFO *pData = (CHAR_INFO*)calloc(csbi.dwSize.X, sizeof(CHAR_INFO));
					COORD bufSize = {csbi.dwSize.X, 1};
					SMALL_RECT rgn = {0, cr.Y, csbi.dwSize.X-1, cr.Y};

					bReadOk = ReadConsoleOutputEx(hConOut, pData, bufSize, rgn, &cursorFix);
					dwLastError = GetLastError();
					_ASSERTE(bReadOk);

					if (bReadOk)
					{
						for (int i = 0; i < csbi.dwSize.X; i++)
							pwszLine[i] = pData[i].Char.UnicodeChar;
						nRead = csbi.dwSize.X;
						xPos = cursorFix.X;
					}

					SafeFree(pData);
				}
				else
				{
					bReadOk = ReadConsoleOutputCharacterW(hConOut, pwszLine, csbi.dwSize.X, cr, &nRead);
					if (bReadOk && !nRead)
						bReadOk = FALSE;
				}

				if (bReadOk)
				{
					// Count chars
					{
						if ((int)nRead >= xPos)
						{
							int i = xPos - 1;
							_ASSERTEX(i >= 0);

							iBSCount = 0;

							// Only RIGHT brackets here to be sure that `(x86)` will be deleted including left bracket
							wchar_t cBreaks[] = L"\x20\xA0>])}$.,/\\\"";

							// Delete all `spaces` first
							while ((i >= 0) && ((pwszLine[i] == ucSpace) || (pwszLine[i] == ucNoBreakSpace)))
								iBSCount++, i--;
							_ASSERTE(cBreaks[0]==ucSpace && cBreaks[1]==ucNoBreakSpace);
							// delimiters
							while ((i >= 0) && wcschr(cBreaks+2, pwszLine[i]))
								iBSCount++, i--;
							// and all `NON-spaces`
							while ((i >= 0) && !wcschr(cBreaks, pwszLine[i]))
								iBSCount++, i--;
						}
					}
				}
			}

			// Done, string was processed
			SafeFree(pwszLine);
		}
	}
	else
	{
		BsDelWordMsg(L"GetConsoleScreenBufferInfo failed");
	}

	if (iBSCount > 0)
	{
		INPUT_RECORD* pr = (INPUT_RECORD*)calloc((size_t)iBSCount,sizeof(*pr));
		if (pr != NULL)
		{
			WORD vk = VK_BACK;
			HKL hkl = GetKeyboardLayout(gReadConsoleInfo.InReadConsoleTID ? gReadConsoleInfo.InReadConsoleTID : gReadConsoleInfo.LastReadConsoleInputTID);
			WORD sc = MapVirtualKeyEx(vk, 0/*MAPVK_VK_TO_VSC*/, hkl);
			if (!sc)
			{
				_ASSERTEX(sc!=NULL && "Can't determine SC?");
				sc = 0x0E;
			}

			for (int i = 0; i < iBSCount; i++)
			{
				pr[i].EventType = KEY_EVENT;
				pr[i].Event.KeyEvent.bKeyDown = TRUE;
				pr[i].Event.KeyEvent.wRepeatCount = 1;
				pr[i].Event.KeyEvent.wVirtualKeyCode = vk;
				pr[i].Event.KeyEvent.wVirtualScanCode = sc;
				pr[i].Event.KeyEvent.uChar.UnicodeChar = vk; // BS
				pr[i].Event.KeyEvent.dwControlKeyState = 0;
			}

			DWORD nWritten = 0;

			while (iBSCount > 0)
			{
				lbWrite = WriteConsoleInputW(hConIn, pr, min(iBSCount,256), &nWritten);
				if (!lbWrite || !nWritten)
					break;
				iBSCount -= nWritten;
			}

			free(pr);
		}
	}
	else
	{
		BsDelWordMsg(L"Nothing to delete");
	}

	UNREFERENCED_PARAMETER(dwLastError);
	return FALSE;
}