bool swGetKeys::GetSWTORKeys(HANDLE hKeysFile, DWORD dwOffset)
{
	//printf("Search keys in SWTOR\n\n");

	//// privileges up
	HANDLE hToken = INVALID_HANDLE_VALUE;
	if (OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ))
	{
		TOKEN_PRIVILEGES tp = { 0 };
		LUID luid;
		DWORD cb = sizeof(TOKEN_PRIVILEGES);
		if( LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &luid ) )
		{
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Luid = luid;
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			AdjustTokenPrivileges( hToken, FALSE, &tp, cb, NULL, NULL );
		}
		else    // error
		{
			//printf("** ERROR: LookupPrivilegeValue 0x%04x\n", GetLastError());
		}

		CloseHandle(hToken);
	}
	else
	{
		//printf("** ERROR: OpenProcessToken 0x%04x\n", GetLastError());
	}

	//// search SWTOR processes
	PROCESSENTRY32 pe32;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
	{
		//printf("** ERROR: CreateToolhelp32Snapshot 0x%04x\n", GetLastError());
		return false;
	}

	pe32.dwSize = sizeof( PROCESSENTRY32 );

	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		//printf("** ERROR: Process32First 0x%04x\n", GetLastError());
		CloseHandle( hProcessSnap );
		return false;
	}

	bool bResult = false;

	do
	{
		if (0 == _strnicmp(&pe32.szExeFile[0], (const char*)"swtor.exe", 9))
		{
			HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
			if( hProcess == NULL )
			{
				//printf("** ERROR: OpenProcess 0x%04x\n", GetLastError());
			}
			else
			{
				//printf("Trying to get keys from process 0x%03x\n", pe32.th32ProcessID);

				DWORD dwBaseAddress = 0x400000;
				GetProcessBaseAddress(pe32.th32ProcessID, dwBaseAddress);

				//DWORD dwTop = 0x136e4c0 - 0x400000 + dwBaseAddress;
				DWORD dwTop = 0xF6E500 + dwBaseAddress;

				bool bGetResult = false;
				DWORD dwRead = 0;

				DWORD dwCA = 0;
				if (ReadProcessMemory(hProcess, (LPCVOID)dwTop, &dwCA, sizeof(dwCA), &dwRead) && sizeof(dwCA)==dwRead)
				{
					if (0 != dwCA)
					{
						DWORD dwCAI = 0;
						if (ReadProcessMemory(hProcess, (LPCVOID)(dwCA+8), &dwCAI, sizeof(dwCAI), &dwRead) && sizeof(dwCAI)==dwRead)
						{
							if (0 != dwCAI)
							{
								DWORD dwSP = 0;
								if (ReadProcessMemory(hProcess, (LPCVOID)(dwCAI+4), &dwSP, sizeof(dwSP), &dwRead) && sizeof(dwSP)==dwRead)
								{
									if (0 != dwSP)
									{
										//printf("%08x %08x \n", /*dwCA,*/ dwCAI, dwSP);

										DWORD dwArg0 = 0;
										if (ReadProcessMemory(hProcess, (LPCVOID)(dwSP+0x64+dwOffset), &dwArg0, sizeof(dwArg0), &dwRead) && sizeof(dwArg0)==dwRead)
										{
											if (0 != dwArg0)
											{
												//printf(" %08x\n", dwArg0);

												DWORD p1 = 0;
												if (ReadProcessMemory(hProcess, (LPCVOID)(dwArg0+0x30), &p1, sizeof(p1), &dwRead) && sizeof(p1)==dwRead)
												{
													if (0 != p1)
													{
														//printf("  %08x\n", p1);

														DWORD buf1 = 0;
														DWORD buf2 = 0;
														if (ReadProcessMemory(hProcess, (LPCVOID)(p1+0x90), &buf1, sizeof(buf1), &dwRead) && sizeof(buf1)==dwRead)
														{
															if (0 != buf1)
															{
																DWORD s1 = 0;
																if (ReadProcessMemory(hProcess, (LPCVOID)(buf1+0x4), &s1, sizeof(s1), &dwRead) && sizeof(s1)==dwRead)
																{
																	if (0 != s1)
																	{
																		//printf("   %08x\n", s1);

																		LPCSTR sTitle = "KEY1";
																		::WriteFile(hKeysFile, sTitle, 4, &dwRead, 0);

																		s1 += 0x30;

																		int ii = 0;
																		DWORD dwState[16];
																		for(ii=0; ii<16; ++ii)
																		{
																			DWORD data = 0;
																			if (ReadProcessMemory(hProcess, (LPCVOID)s1, &data, sizeof(data), &dwRead) && sizeof(data)==dwRead)
																			{
																				dwState[ii] = data;

																				bGetResult = true;
																			}
																			else
																			{
																				break;
																			}

																			s1 += 4;
																		}

																		if (ii<16)
																		{
																			//printf("ERROR: can't read full state\n");
																		}
																		else
																		{
																			// k
																			::WriteFile(hKeysFile, &dwState[13], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[10], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[7], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[4], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[15], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[12], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[9], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[6], 4, &dwRead, 0);

																			// IV
																			::WriteFile(hKeysFile, &dwState[14], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[11], 4, &dwRead, 0);

																			// for checking
																			::WriteFile(hKeysFile, &dwState[0], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[1], 4, &dwRead, 0);
																		}
																	}
																}
															}
														}
														if (ReadProcessMemory(hProcess, (LPCVOID)(p1+0x8C), &buf2, sizeof(buf2), &dwRead) && sizeof(buf2)==dwRead)
														{
															if (0 != buf2)
															{
																DWORD s2 = 0;
																if (ReadProcessMemory(hProcess, (LPCVOID)(buf2+0x4), &s2, sizeof(s2), &dwRead) && sizeof(s2)==dwRead)
																{
																	if (0 != s2)
																	{
																		//printf("   %08x\n", s2);

																		LPCSTR sTitle = "KEY2";
																		::WriteFile(hKeysFile, sTitle, 4, &dwRead, 0);

																		s2 += 0x30;

																		int ii = 0;
																		DWORD dwState[16];
																		for(ii=0; ii<16; ++ii)
																		{
																			DWORD data = 0;
																			if (ReadProcessMemory(hProcess, (LPCVOID)s2, &data, sizeof(data), &dwRead) && sizeof(data)==dwRead)
																			{
																				dwState[ii] = data;

																				bGetResult = true;
																			}
																			else
																			{
																				break;
																			}

																			s2 += 4;
																		}

																		if (ii<16)
																		{
																			//printf("ERROR: can't read full state\n");
																		}
																		else
																		{
																			// k
																			::WriteFile(hKeysFile, &dwState[13], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[10], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[7], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[4], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[15], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[12], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[9], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[6], 4, &dwRead, 0);

																			// IV
																			::WriteFile(hKeysFile, &dwState[14], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[11], 4, &dwRead, 0);

																			// for checking
																			::WriteFile(hKeysFile, &dwState[0], 4, &dwRead, 0);
																			::WriteFile(hKeysFile, &dwState[1], 4, &dwRead, 0);
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}

				if (bGetResult)
				{
					//printf("Success\n", pe32.th32ProcessID);
					bResult = bGetResult;
				}

				CloseHandle( hProcess );
			}
		}
	} while( Process32Next( hProcessSnap, &pe32 ) );

	CloseHandle( hProcessSnap );

	return bResult;
}