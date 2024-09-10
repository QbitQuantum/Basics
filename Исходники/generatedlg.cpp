	void GenerateApk(std::wstring path )
	{
		//if ( !JREInstalled() )
		//{
		//	MessageBoxW(NULL, L"未安装 java 运行环境，无法生成 apk 安装包，请安装 java 运行环境后重试!", L"提示", MB_OK | MB_ICONINFORMATION);
		//	return;
		//}

		SHELLEXECUTEINFOW sei;
		memset(&sei, 0, sizeof(SHELLEXECUTEINFO)); 
		std::wstring installPath = GetExePath() + L"\\dependency\\Android\\Remote\\install.exe";
		wchar_t cmd[1024] = {0};
		wsprintfW(cmd, L"-i \"%s\" -o \"%s\"", GetExePath().c_str(), path.c_str());

		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
		sei.lpVerb = L"open";
		sei.lpFile = installPath.c_str();
		sei.lpParameters = cmd;
		sei.nShow = SW_HIDE;

		PVOID oldValue = NULL;
		if ( Is64Bit() && !oldValue )
		{
			HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
			pWow64DisableWow64FsRedirection foo = (pWow64DisableWow64FsRedirection)GetProcAddress(kernel32, "Wow64DisableWow64FsRedirection");
			foo(&oldValue);
		}

		ShellExecuteExW(&sei);
		WaitForSingleObject(sei.hProcess, INFINITE);
		CloseHandle(sei.hProcess);

		if ( Is64Bit() && oldValue )
		{
			HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
			pWow64RevertWow64FsRedirection foo = (pWow64RevertWow64FsRedirection)GetProcAddress(kernel32, "Wow64RevertWow64FsRedirection");
			foo(oldValue);
		}


	}