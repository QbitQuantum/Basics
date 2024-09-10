// Returns ">0" - when changes was made
//  0 - no changes
// -1 - error
// bForceCurConsole==true, если разбор параметров идет 
//   при запуске Tasks из GUI
int RConStartArgs::ProcessNewConArg(bool bForceCurConsole /*= false*/)
{
	bNewConsole = FALSE;

	if (!pszSpecialCmd || !*pszSpecialCmd)
	{
		_ASSERTE(pszSpecialCmd && *pszSpecialCmd);
		return -1;
	}

	int nChanges = 0;
	
	// 120115 - Если первый аргумент - "ConEmu.exe" или "ConEmu64.exe" - не обрабатывать "-cur_console" и "-new_console"
	{
		LPCWSTR pszTemp = pszSpecialCmd;
		wchar_t szExe[MAX_PATH+1];
		if (0 == NextArg(&pszTemp, szExe))
		{
			pszTemp = PointToName(szExe);
			if (lstrcmpi(pszTemp, L"ConEmu.exe") == 0
				|| lstrcmpi(pszTemp, L"ConEmu") == 0
				|| lstrcmpi(pszTemp, L"ConEmu64.exe") == 0
				|| lstrcmpi(pszTemp, L"ConEmu64") == 0)
			{
				return 0;
			}
		}
	}
	

	// 111211 - здесь может быть передан "-new_console:..."
	LPCWSTR pszNewCon = L"-new_console";
	// 120108 - или "-cur_console:..." для уточнения параметров запуска команд (из фара например)
	LPCWSTR pszCurCon = L"-cur_console";
	int nNewConLen = lstrlen(pszNewCon);
	_ASSERTE(lstrlen(pszCurCon)==nNewConLen);
	bool bStop = false;

	while (!bStop)
	{
		wchar_t* pszFindNew = wcsstr(pszSpecialCmd, pszNewCon);
		wchar_t* pszFind = pszFindNew ? pszFindNew : wcsstr(pszSpecialCmd, pszCurCon);
		if (pszFindNew)
			bNewConsole = TRUE;
		else if (!pszFind)
			break;

		// Проверка валидности
		_ASSERTE(pszFind >= pszSpecialCmd);
		if (((pszFind == pszSpecialCmd) || (*(pszFind-1) == L'"') || (*(pszFind-1) == L' ')) // начало аргумента
			&& (pszFind[nNewConLen] == L' ' || pszFind[nNewConLen] == L':' 
				|| pszFind[nNewConLen] == L'"' || pszFind[nNewConLen] == 0))
		{
			// -- не будем пока, мешает. например, при запуске задач
			//// По умолчанию, принудительно включить "Press Enter or Esc to close console"
			//if (!bForceCurConsole)
			//	eConfirmation = eConfAlways;
		
			bool lbQuot = (*(pszFind-1) == L'"');
			const wchar_t* pszEnd = pszFind+nNewConLen;
			//wchar_t szNewConArg[MAX_PATH+1];
			if (lbQuot)
				pszFind--;

			if (*pszEnd == L'"')
			{
				pszEnd++;
			}
			else if (*pszEnd != L':')
			{
				// Конец
				_ASSERTE(*pszEnd == L' ' || *pszEnd == 0);
			}
			else
			{
				if (*pszEnd == L':')
				{
					pszEnd++;
				}
				else
				{
					_ASSERTE(*pszEnd == L':');
				}

				// Обработка доп.параметров -new_console:xxx
				bool lbReady = false;
				while (!lbReady && *pszEnd)
				{
					wchar_t cOpt = *(pszEnd++);
					switch (cOpt)
					{
					//case L'-':
					//	bStop = true; // следующие "-new_console" - не трогать!
					//	break;
					case L'"':
					case L' ':
					case 0:
						lbReady = true;
						break;
						
					case L'b':
						// b - background, не активировать таб
						bBackgroundTab = TRUE; bForegroungTab = FALSE;
						break;
					case L'f':
						// f - foreground, активировать таб (аналог ">" в Tasks)
						bForegroungTab = TRUE; bBackgroundTab = FALSE;
						break;

					case L'z':
						// z - don't use "Default terminal" feature
						bNoDefaultTerm = TRUE;
						break;
						
					case L'a':
						// a - RunAs shell verb (as admin on Vista+, login/password in WinXP-)
						bRunAsAdministrator = TRUE;
						break;
						
					case L'r':
						// r - run as restricted user
						bRunAsRestricted = TRUE;
						break;
						
					case L'o':
						// o - disable "Long output" for next command (Far Manager)
						bLongOutputDisable = TRUE;
						break;

					case L'w':
						// e - enable "Overwrite" mode in console prompt
						bOverwriteMode = TRUE;
						break;

					case L'p':
						if (isDigit(*pszEnd))
						{
							switch (*(pszEnd++))
							{
								case L'0':
									nPTY = 0; // don't change
									break;
								case L'1':
									nPTY = 1; // enable PTY mode
									break;
								case L'2':
									nPTY = 2; // disable PTY mode (switch to plain $CONIN, $CONOUT, $CONERR)
									break;
								default:
									nPTY = 1;
							}
						}
						else
						{
							nPTY = 1; // enable PTY mode
						}
						break;

					case L'i':
						// i - don't inject ConEmuHk into the starting application
						bInjectsDisable = TRUE;
						break;

					case L'h':
						// "h0" - отключить буфер, "h9999" - включить буфер в 9999 строк
						{
							bBufHeight = TRUE;
							if (isDigit(*pszEnd))
							{
								wchar_t* pszDigits = NULL;
								nBufHeight = wcstoul(pszEnd, &pszDigits, 10);
								if (pszDigits)
									pszEnd = pszDigits;
							}
							else
							{
								nBufHeight = 0;
							}
						} // L'h':
						break;
						
					case L'n':
						// n - отключить "Press Enter or Esc to close console"
						eConfirmation = eConfNever;
						break;
						
					case L'c':
						// c - принудительно включить "Press Enter or Esc to close console"
						eConfirmation = eConfAlways;
						break;
						
					case L'x':
						// x - Force using dosbox for .bat files
						bForceDosBox = TRUE;
						break;

					case L'I':
						// I - tell GuiMacro to execute new command inheriting active process state. This is only usage ATM.
						bForceInherit = TRUE;
						break;
						
					// "Long" code blocks below: 'd', 'u', 's' and so on (in future)
					case L'd':
						// d:<StartupDir>. MUST be last options
						{
							if (*pszEnd == L':')
								pszEnd++;
							const wchar_t* pszDir = pszEnd;
							while ((*pszEnd) && (lbQuot || *pszEnd != L' ') && (*pszEnd != L'"'))
								pszEnd++;
							if (pszEnd > pszDir)
							{
								size_t cchLen = pszEnd - pszDir;
								SafeFree(pszStartupDir);
								pszStartupDir = (wchar_t*)malloc((cchLen+1)*sizeof(*pszStartupDir));
								if (pszStartupDir)
								{
									wmemmove(pszStartupDir, pszDir, cchLen);
									pszStartupDir[cchLen] = 0;
									// Например, "%USERPROFILE%"
									if (wcschr(pszStartupDir, L'%'))
									{
										wchar_t* pszExpand = NULL;
										if (((pszExpand = ExpandEnvStr(pszStartupDir)) != NULL))
										{
											SafeFree(pszStartupDir);
											pszStartupDir = pszExpand;
										}
									}
								}
							}
						} // L'd':
						break;

					case L't':
						// t:<TabName>. MUST be last options
					case L'C':
						// C:<IconFile>. MUST be last options
					case L'P':
						// P:<Palette>. MUST be last options
					case L'W':
						// W:<Wallpaper>. MUST be last options
						{
							if (*pszEnd == L':')
								pszEnd++;
							const wchar_t* pszTab = pszEnd;
							while ((*pszEnd) && (lbQuot || *pszEnd != L' ') && (*pszEnd != L'"'))
								pszEnd++;
							if (pszEnd > pszTab)
							{
								wchar_t** pptr = NULL;
								switch (cOpt)
								{
								case L't': pptr = &pszRenameTab; break;
								case L'C': pptr = &pszIconFile; break;
								case L'P': pptr = &pszPalette; break;
								case L'W': pptr = &pszWallpaper; break;
								}
								size_t cchLen = pszEnd - pszTab;
								SafeFree(*pptr);
								*pptr = (wchar_t*)malloc((cchLen+1)*sizeof(**pptr));
								if (*pptr)
								{
									// We need to process escape sequences ("^>" -> ">", "^&" -> "&", etc.)
									//wmemmove(*pptr, pszTab, cchLen);
									wchar_t* pD = *pptr;
									const wchar_t* pS = pszTab;
									// There is enough room allocated
									while (pS < pszEnd)
									{
										if ((*pS == L'^') && ((pS + 1) < pszEnd))
											pS++; // Skip control char, goto escaped char
										else if ((*pS == L'"') && ((pS + 1) < pszEnd) && (*(pS+1) == L'"'))
											pS++; // Skip qoubled qouble quote

										*(pD++) = *(pS++);
									}
									// Terminate with '\0'
									_ASSERTE(pD <= ((*pptr)+cchLen));
									*pD = 0;
								}
							}
						} // L't':
						break;

					case L's':
						// s[<SplitTab>T][<Percents>](H|V)
						// Пример: "s3T30H" - разбить 3-ий таб. будет создан новый Pane справа, шириной 30% от 3-го таба.
						{
							UINT nTab = 0 /*active*/, nValue = /*пополам*/DefaultSplitValue/10;
							bool bDisableSplit = false;
							while (*pszEnd)
							{
								if (isDigit(*pszEnd))
								{
									wchar_t* pszDigits = NULL;
									UINT n = wcstoul(pszEnd, &pszDigits, 10);
									if (!pszDigits)
										break;
									pszEnd = pszDigits;
									if (*pszDigits == L'T')
									{
                                    	nTab = n;
                                	}
                                    else if ((*pszDigits == L'H') || (*pszDigits == L'V'))
                                    {
                                    	nValue = n;
                                    	eSplit = (*pszDigits == L'H') ? eSplitHorz : eSplitVert;
                                    }
                                    else
                                    {
                                    	break;
                                    }
                                    pszEnd++;
								}
								else if (*pszEnd == L'T')
								{
									nTab = 0;
									pszEnd++;
								}
								else if ((*pszEnd == L'H') || (*pszEnd == L'V'))
								{
	                            	nValue = DefaultSplitValue/10;
	                            	eSplit = (*pszEnd == L'H') ? eSplitHorz : eSplitVert;
	                            	pszEnd++;
								}
								else if (*pszEnd == L'N')
								{
									bDisableSplit = true;
									pszEnd++;
									break;
								}
								else
								{
									break;
								}
							}

							if (bDisableSplit)
							{
								eSplit = eSplitNone; nSplitValue = DefaultSplitValue; nSplitPane = 0;
							}
							else
							{
								if (!eSplit)
									eSplit = eSplitHorz;
								// Для удобства, пользователь задает размер НОВОЙ части
								nSplitValue = 1000-max(1,min(nValue*10,999)); // проценты
								_ASSERTE(nSplitValue>=1 && nSplitValue<1000);
								nSplitPane = nTab;
							}
						} // L's'
						break;
						
					case L'u':
						{
							// u - ConEmu choose user dialog
							// u:<user>:<pwd> - specify user/pwd in args. MUST be last option
							
							lbReady = true; // последняя опция

							SafeFree(pszUserName);
							SafeFree(pszDomain);
							if (szUserPassword[0]) SecureZeroMemory(szUserPassword, sizeof(szUserPassword));
							
							if (*pszEnd == L':')
							{
								pszEnd++;
								
								wchar_t szUser[MAX_PATH], *p = szUser, *p2 = szUser+countof(szUser)-1;
								while (*pszEnd && (p < p2))
								{
									if ((*pszEnd == 0) || (*pszEnd == L':') || (*pszEnd == L'"'))
									{
										break;
									}
									//else if (*pszEnd == L'"' && *(pszEnd+1) == L'"')
									//{
									//	*(p++) = L'"'; pszEnd += 2;
									//}
									else if (*pszEnd == L'^')
									{
										pszEnd++;
										*(p++) = *(pszEnd++);
									}
									else
									{
										*(p++) = *(pszEnd++);
									}
								}
								*p = 0;

								wchar_t* pszSlash = wcschr(szUser, L'\\');
								if (pszSlash)
								{
									*pszSlash = 0;
									pszDomain = lstrdup(szUser);
									pszUserName = lstrdup(pszSlash+1);
								}
								else
								{
									pszUserName = lstrdup(szUser);
								}
								
								if (*pszEnd == L':')
								{
									pszEnd++;
									//lstrcpyn(szUserPassword, pszPwd, countof(szUserPassword));

									p = szUserPassword; p2 = szUserPassword+countof(szUserPassword)-1;
									while (*pszEnd && (p < p2))
									{
										if ((*pszEnd == 0) || (*pszEnd == L':') || (*pszEnd == L'"'))
										{
											break;
										}
										else if (*pszEnd == L'^')
										{
											pszEnd++;
											*(p++) = *(pszEnd++);
										}
										else
										{
											*(p++) = *(pszEnd++);
										}
									}
									*p = 0;

								}
							}
							else
							{
								bForceUserDialog = TRUE;
							}
						} // L'u'
						break;
					}
				}
			}

			if (pszEnd > pszFind)
			{
				// pszEnd должен указывать на конец -new_console[:...] / -cur_console[:...]
				// и включать обрамляющую кавычку, если он окавычен
				if (lbQuot)
				{
					if (*pszEnd == L'"' && *(pszEnd-1) != L'"')
						pszEnd++;
				}
				else
				{
					while (*(pszEnd-1) == L'"')
						pszEnd--;
				}

				// Откусить лишние пробелы, которые стоят ПЕРЕД -new_console[:...] / -cur_console[:...]
				while (((pszFind - 1) > pszSpecialCmd)
					&& (*(pszFind-1) == L' ')
					&& ((*(pszFind-2) == L' ') || (/**pszEnd == L'"' ||*/ *pszEnd == 0 || *pszEnd == L' ')))
				{
					pszFind--;
				}

				wmemmove(pszFind, pszEnd, (lstrlen(pszEnd)+1));
				nChanges++;
			}
			else
			{
				_ASSERTE(pszEnd > pszFind);
				*pszFind = 0;
				nChanges++;
			}
		}
	}

	return nChanges;
}