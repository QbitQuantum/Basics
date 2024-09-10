bool GetImageSubsystem(PROCESS_INFORMATION pi,DWORD& ImageSubsystem,DWORD& ImageBits/*16/32/64*/)
{
	DWORD nErrCode = 0;
	DWORD nFlags = TH32CS_SNAPMODULE;
	
	ImageBits = 32; //-V112
	ImageSubsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI;
	
	#ifdef _WIN64
		HMODULE hKernel = GetModuleHandle(L"kernel32.dll");
		if (hKernel)
		{
			typedef BOOL (WINAPI* IsWow64Process_t)(HANDLE, PBOOL);
			IsWow64Process_t IsWow64Process_f = (IsWow64Process_t)GetProcAddress(hKernel, "IsWow64Process");

			if (IsWow64Process_f)
			{
				BOOL bWow64 = FALSE;
				if (IsWow64Process_f(pi.hProcess, &bWow64) && !bWow64)
				{
					ImageBits = 64;
				}
				else
				{
					ImageBits = 32;
					nFlags = TH32CS_SNAPMODULE32;
				}
			}
		}
	#endif
	
	HANDLE hSnap = CreateToolhelp32Snapshot(nFlags, pi.dwProcessId);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		nErrCode = GetLastError();
		return false;
	}
	IMAGE_DOS_HEADER dos;
	IMAGE_HEADERS hdr;
	SIZE_T hdrReadSize;
	MODULEENTRY32 mi = {sizeof(MODULEENTRY32)};
	BOOL lbModule = Module32First(hSnap, &mi);
	CloseHandle(hSnap);
	if (!lbModule)
		return false;
	
	// Теперь можно считать данные процесса
	if (!ReadProcessMemory(pi.hProcess, mi.modBaseAddr, &dos, sizeof(dos), &hdrReadSize))
		nErrCode = -3;
	else if (dos.e_magic != IMAGE_DOS_SIGNATURE)
		nErrCode = -4; // некорректная сигнатура - должно быть 'MZ'
	else if (!ReadProcessMemory(pi.hProcess, mi.modBaseAddr+dos.e_lfanew, &hdr, sizeof(hdr), &hdrReadSize))
		nErrCode = -5;
	else if (hdr.Signature != IMAGE_NT_SIGNATURE)
		nErrCode = -6;
	else if (hdr.OptionalHeader32.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC
	        &&  hdr.OptionalHeader64.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
		nErrCode = -7;
	else
	{
		nErrCode = 0;
		
		switch (hdr.OptionalHeader32.Magic)
		{
			case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
			{
				_ASSERTE(ImageBits == 32); //-V112
				ImageBits = 32; //-V112
				ImageSubsystem = hdr.OptionalHeader32.Subsystem;
				_ASSERTE((ImageSubsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI) || (ImageSubsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI));
			}
			break;
			case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
			{
				_ASSERTE(ImageBits == 64);
				ImageBits = 64;
				ImageSubsystem = hdr.OptionalHeader64.Subsystem;
				_ASSERTE((ImageSubsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI) || (ImageSubsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI));
			}
			break;
			default:
			{
				nErrCode = -8;
			}
		}
	}
	
	return (nErrCode == 0);
}