SleshLibrary::SleshLibrary(const char* moduleName) {
	find_module_path(moduleName);
	hmod = NULL;
	string error;
	ULONG retadr = 0;
	DWORD rb;
	HANDLE hFile;
	IMAGE_DOS_HEADER DosHeader;
	IMAGE_NT_HEADERS PeHeader;
	IMAGE_SECTION_HEADER Section[MAX_SECTIONS];
	char tmp[1024];

	// откроем файл на чтение
	string path = find_module_path(moduleName);
	hFile = CreateFileA(path.c_str(),
		GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		getLastError(error, "CreateFile");
		error += ": ";
		error += moduleName;
		throw DllException(error.c_str());
	}

	// считаем DOS заголовок
	if ( ReadFile(hFile, &DosHeader, sizeof(IMAGE_DOS_HEADER), &rb, 0) == 0 ) {
		getLastError(error, "ReadFile");
		CloseHandle(hFile);
		throw DllException(error.c_str());
	}

	if (DosHeader.e_magic == IMAGE_DOS_SIGNATURE) { // проверим сигнатуру
		// если есть какимето данные между DOS заголовком и PE 
		// то считаем их. В MS компиляторах это часто Rich данные
		if (sizeof(IMAGE_DOS_HEADER) < DosHeader.e_lfanew) {
			if ( ReadFile(hFile, &tmp[0], DosHeader.e_lfanew -
				sizeof(IMAGE_DOS_HEADER), &rb, 0) == 0 )
			{
				getLastError(error, "ReadFile");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
		}
		// установим указатель в файле на PE заголовок
		if ( SetFilePointer(hFile, DosHeader.e_lfanew, 0, FILE_BEGIN) ==
			INVALID_SET_FILE_POINTER )
		{
			getLastError(error, "SetFilePointer");
			CloseHandle(hFile);
			throw DllException(error.c_str());
		}
		// считаем заголовок
		if ( ReadFile(hFile, &PeHeader, sizeof(IMAGE_NT_HEADERS), &rb, 0) == 0 ) {
			getLastError(error, "ReadFile");
			CloseHandle(hFile);
			throw DllException(error.c_str());
		}

		if ( PeHeader.Signature == IMAGE_NT_SIGNATURE ) { // проверим сигнатуру
			// считаем 10 секций
			if ( ReadFile(hFile, &Section[0], sizeof(IMAGE_SECTION_HEADER) *
				PeHeader.FileHeader.NumberOfSections, &rb, 0) == 0 ) 
			{
				getLastError(error, "ReadFile");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
			// выделим память столько, сколько указано в SIZE OF BASE
			retadr = (ULONG)VirtualAlloc(0, PeHeader.OptionalHeader.SizeOfImage,
				MEM_COMMIT | MEM_RESERVE | MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);
			if ( retadr == NULL ) {
				getLastError(error, "VirtualAlloc");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
			
			// скопируем туда DOS заголовок
			memcpy((void*) retadr, &DosHeader, sizeof(IMAGE_DOS_HEADER));
			// скопируем туда PE заголовок
			memcpy((void*)(retadr + DosHeader.e_lfanew), &PeHeader,
				sizeof(IMAGE_NT_HEADERS));
			// скопируем туда таблицу секций
			memcpy((void*)(retadr + DosHeader.e_lfanew + sizeof(IMAGE_NT_HEADERS)),
				&Section[0], sizeof(IMAGE_SECTION_HEADER) *
				PeHeader.FileHeader.NumberOfSections);
			// если есть Rich данные то и их тоже скопируем
			if ( sizeof(IMAGE_DOS_HEADER) < DosHeader.e_lfanew )  {
				memcpy((void*)(retadr + sizeof(IMAGE_DOS_HEADER)), &tmp[0],
					DosHeader.e_lfanew - sizeof(IMAGE_DOS_HEADER));
			}
			// обработаем каждую секцию
			for ( int i = 0; i < PeHeader.FileHeader.NumberOfSections; i++ ){
				// установим указатель в файле не начало секции в файле
				if ( SetFilePointer(hFile, Section[i].PointerToRawData, 0, FILE_BEGIN) ==
					INVALID_SET_FILE_POINTER )
				{
					getLastError(error, "SetFilePointer");
					CloseHandle(hFile);
					VirtualFree((LPVOID)retadr, 0, MEM_RELEASE); // очищаем память
					throw DllException(error.c_str());
				}
				// считаем всё секцию
				if ( ReadFile(hFile, (void*)(retadr + Section[i].VirtualAddress),
					Section[i].SizeOfRawData, &rb,0) == 0 )
				{
					getLastError(error, "ReadFile");
					CloseHandle(hFile);
					VirtualFree((LPVOID)retadr, 0, MEM_RELEASE);
					throw DllException(error.c_str());
				}
			}

			CloseHandle(hFile);

			// Обработаем релоки
			try {
				progressReloc(retadr);
				progressImport(retadr);
			} catch ( DllException e ) {
				VirtualFree((LPVOID)retadr, 0, MEM_RELEASE);
				throw DllException(e.what());
			}

			__asm {
				mov eax, PeHeader.OptionalHeader.AddressOfEntryPoint
				add eax, retadr // EAX = ENTRY POINT
				push 0
				push DLL_PROCESS_ATTACH // ставим флаг что подгрузили DLL
				push retadr
				call eax // передадим управление на точку входа в DLL 
			}
			hmod = (HMODULE)retadr;
		}
	}
}