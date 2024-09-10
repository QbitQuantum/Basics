BOOL WINAPI SSQ_AddressToFunctionName(DWORD address,char** module,char** function)
{
	static HANDLE handle_snapshot;
	static MODULEENTRY32 module_entry;
	static BOOL module_next;
	static PIMAGE_DOS_HEADER dos_header;
	static PIMAGE_NT_HEADERS nt_headers;
	static PIMAGE_EXPORT_DIRECTORY export_directory;
	static DWORD counter;
	static DWORD counter2;

	if(HIWORD(address)==0||HIWORD(module)==0||HIWORD(function)==0)
	{
		return FALSE;
	}

	handle_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetCurrentProcessId());

	if(handle_snapshot==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	module_entry.dwSize = sizeof(module_entry);

	if(Module32First(handle_snapshot,&module_entry)==FALSE)
	{
		CloseHandle(handle_snapshot);

		return FALSE;
	}

	do
	{
		if(address>=(DWORD)module_entry.modBaseAddr&&address<((DWORD)module_entry.modBaseAddr+module_entry.modBaseSize))
		{
			*module = module_entry.szModule;

			break;
		}
	}
	while((module_next = Module32Next(handle_snapshot,&module_entry))==TRUE);

	CloseHandle(handle_snapshot);

	if(module_next==FALSE)
	{
		return FALSE;
	}

	dos_header = (PIMAGE_DOS_HEADER)module_entry.modBaseAddr;
	nt_headers = (PIMAGE_NT_HEADERS)((DWORD)dos_header+dos_header->e_lfanew);
	export_directory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)dos_header+nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	for(counter = 0;counter<export_directory->NumberOfFunctions;counter++)
	{
		if(((DWORD)dos_header+((PULONG)((DWORD)dos_header+(DWORD)export_directory->AddressOfFunctions))[counter])==address)
		{
			for(counter2 = 0;counter2<export_directory->NumberOfNames;counter2++)
			{
				if(((PUSHORT)((DWORD)dos_header+(DWORD)export_directory->AddressOfNameOrdinals))[counter2]==counter)
				{
					*function = (char*)((DWORD)dos_header+((PULONG)((DWORD)dos_header+(DWORD)export_directory->AddressOfNames))[counter2]);

					//wsprintf(test,"c: %i c2 %i address: 0x%08X ordinal: %i %08X aof %08X",counter,counter2,address,ordinal,(DWORD)dos_header+(DWORD)export_directory->AddressOfNameOrdinals,(DWORD)dos_header+(DWORD)export_directory->AddressOfFunctions);
					//MessageBox(0,*function,test,0);

					return TRUE;				
				}
			}
		}
	}

	return FALSE;
}