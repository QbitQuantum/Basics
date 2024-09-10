//*************************************************************
LLSD WINAPI Get_Exception_Info(PEXCEPTION_POINTERS pException)
//*************************************************************
// Allocate Str[DUMP_SIZE_MAX] and return Str with dump, if !pException - just return call stack in Str.
{
	LLSD info;
	LPWSTR		Str;
	int			Str_Len;
//	int			i;
	LPWSTR		Module_Name = new WCHAR[MAX_PATH];
	PBYTE		Module_Addr;
	HANDLE		hFile;
	FILETIME	Last_Write_Time;
	FILETIME	Local_File_Time;
	SYSTEMTIME	T;

	Str = new WCHAR[DUMP_SIZE_MAX];
	Str_Len = 0;
	if (!Str)
		return NULL;
	
	Get_Version_Str(info);
	
	GetModuleFileName(NULL, Str, MAX_PATH);
	info["Process"] = ll_convert_wide_to_string(Str);
	info["ThreadID"] = (S32)GetCurrentThreadId();

	// If exception occurred.
	if (pException)
	{
		EXCEPTION_RECORD &	E = *pException->ExceptionRecord;
		CONTEXT &			C = *pException->ContextRecord;

		// If module with E.ExceptionAddress found - save its path and date.
		if (Get_Module_By_Ret_Addr((PBYTE)E.ExceptionAddress, Module_Name, Module_Addr))
		{
			info["Module"] = ll_convert_wide_to_string(Module_Name);

			if ((hFile = CreateFile(Module_Name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
			{
				if (GetFileTime(hFile, NULL, NULL, &Last_Write_Time))
				{
					FileTimeToLocalFileTime(&Last_Write_Time, &Local_File_Time);
					FileTimeToSystemTime(&Local_File_Time, &T);

					info["DateModified"] = llformat("%02d/%02d/%d", T.wMonth, T.wDay, T.wYear);
				}
				CloseHandle(hFile);
			}
		}
		else
		{
			info["ExceptionAddr"] = (int)E.ExceptionAddress;
		}
		
		info["ExceptionCode"] = (int)E.ExceptionCode;
		
		/*
		//TODO: Fix this
		if (E.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
		{
			// Access violation type - Write/Read.
			LLSD exception_info;
			exception_info["Type"] = E.ExceptionInformation[0] ? "Write" : "Read";
			exception_info["Address"] = llformat("%08x", E.ExceptionInformation[1]);
			info["Exception Information"] = exception_info;
		}
		*/

		
		// Save instruction that caused exception.
		/*
		std::string str;
		for (i = 0; i < 16; i++)
			str += llformat(" %02X", PBYTE(E.ExceptionAddress)[i]);
		info["Instruction"] = str;
		*/
		LLSD registers;
		registers["EAX"] = (int)C.Eax;
		registers["EBX"] = (int)C.Ebx;
		registers["ECX"] = (int)C.Ecx;
		registers["EDX"] = (int)C.Edx;
		registers["ESI"] = (int)C.Esi;
		registers["EDI"] = (int)C.Edi;
		registers["ESP"] = (int)C.Esp;
		registers["EBP"] = (int)C.Ebp;
		registers["EIP"] = (int)C.Eip;
		registers["EFlags"] = (int)C.EFlags;
		info["Registers"] = registers;
	} //if (pException)
	
	// Save call stack info.
	Get_Call_Stack(pException->ExceptionRecord, pException->ContextRecord, info);

	return info;
} //Get_Exception_Info