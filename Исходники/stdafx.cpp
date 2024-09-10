void UpdateMemoryMap(void)
{
	MemMap.clear();
	MemMapCode.clear();
	MemMapData.clear();
	MemMapModule.clear();
	Exports.clear();
	CustomNames.clear();

	if (hProcess == NULL)
		return;
	if (!IsProcHandleValid(hProcess))
	{
		hProcess = NULL;
		return;
	}

	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);

	MEMORY_BASIC_INFORMATION MBI;
	ULONG_PTR pMemory = (ULONG_PTR)SysInfo.lpMinimumApplicationAddress;
	while(pMemory < (ULONG_PTR)SysInfo.lpMaximumApplicationAddress)
	{
		if ( VirtualQueryEx(hProcess,(LPCVOID)pMemory,&MBI,sizeof(MBI)) != 0)
		{
			if (MBI.State == MEM_COMMIT /*&& MBI.Type == MEM_PRIVATE*/)
			{
				MemMapInfo Mem;
				Mem.Start = (DWORD_PTR)pMemory;
				Mem.End = (DWORD_PTR)pMemory + MBI.RegionSize - 1;
				MemMap.push_back(Mem);
			}
			pMemory = (ULONG_PTR)MBI.BaseAddress + MBI.RegionSize;
		}
		else
		{
			pMemory += 1024;
		}
	}

	MODULEENTRY32	ModInfo;
	ModInfo.dwSize		= sizeof(MODULEENTRY32);

	HANDLE ModuleList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetProcessId(hProcess));
	if ((int)ModuleList != -1)
	{
		BOOL rm = Module32First(ModuleList,&ModInfo);
		while(rm)
		{
			MemMapInfo Mem;
			Mem.Start = (DWORD_PTR)ModInfo.modBaseAddr;
			Mem.End = Mem.Start + ModInfo.modBaseSize;
			Mem.Name = ModInfo.szModule;
			MemMapModule.push_back(Mem);

			rm = Module32Next(ModuleList,&ModInfo);
		}
		CloseHandle(ModuleList);
	}

	AddressName Entry;
	ModuleList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetProcessId(hProcess));
	if ((int)ModuleList != -1)
	{
		BOOL rm = Module32First(ModuleList,&ModInfo);
		while(rm)
		{
			IMAGE_DOS_HEADER DH;
			IMAGE_NT_HEADERS pe;

			ReadProcessMemory(hProcess,ModInfo.modBaseAddr,&DH,sizeof(DH),NULL);
			ReadProcessMemory(hProcess,ModInfo.modBaseAddr + DH.e_lfanew,&pe,sizeof(pe),NULL);
			DWORD ssize = (DWORD)pe.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
			PIMAGE_SECTION_HEADER sh = (PIMAGE_SECTION_HEADER)(new char[ssize]);
			ReadProcessMemory(hProcess,ModInfo.modBaseAddr + DH.e_lfanew + sizeof(IMAGE_NT_HEADERS),sh,ssize,NULL);
			for (int i=0; i < pe.FileHeader.NumberOfSections; i++)
			{
				CString txt;
				MemMapInfo Mem;
				txt.Format("%.8s",sh[i].Name); txt.MakeLower();
				if (txt == ".text" || txt == "code")
				{
					Mem.Start	= (DWORD_PTR)ModInfo.modBaseAddr + sh[i].VirtualAddress;
					Mem.End		= Mem.Start + sh[i].Misc.VirtualSize;
					Mem.Name	= ModInfo.szModule;
					MemMapCode.push_back(Mem);
				}
				if (txt == ".data" || txt == "data" || txt == ".rdata" || txt == ".idata")
				{
					Mem.Start	= (DWORD_PTR)ModInfo.modBaseAddr + sh[i].VirtualAddress;
					Mem.End		= Mem.Start + sh[i].Misc.VirtualSize;
					Mem.Name	= ModInfo.szModule;
					MemMapData.push_back(Mem);
				}
			}
			delete sh;

			rm = Module32Next(ModuleList,&ModInfo);
		}
		CloseHandle(ModuleList);
	}

	for (UINT i=0; i<MemMap.size();i++)
	{
		if (IsModule(MemMap[i].Start)) MemMap[i].Name = GetModuleName(MemMap[i].Start);
	}
}