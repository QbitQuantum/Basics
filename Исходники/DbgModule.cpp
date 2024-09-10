	HRESULT Init(std::shared_ptr<CDbgEngine> _engine, LPCTSTR modname)
	{
		engine = _engine;

		// まずイメージを開きます。
		file = CreateFile(
			modname, GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, 0, NULL);
		if (file == INVALID_HANDLE_VALUE) {
			assert(!"Couldn't open the image file.");
			return HRESULT_FROM_WIN32(::GetLastError());
		}

		mapfile = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
		if (mapfile == NULL) {
			//CloseHandle(file);
			return HRESULT_FROM_WIN32(::GetLastError());
		}

		LPBYTE pbase = (LPBYTE)MapViewOfFile(mapfile, FILE_MAP_READ, 0, 0, 0);
		if (pbase == NULL) {
			//CloseHandle(mapfile);
			//CloseHandle(file);
			return HRESULT_FROM_WIN32(::GetLastError());
		}

		// PEヘッダを取得します。
		ntheader = engine->ImageNtHeader(pbase);
		if (ntheader == NULL
			|| ntheader->FileHeader.Machine != IMAGE_FILE_MACHINE_I386
			|| ntheader->FileHeader.SizeOfOptionalHeader == 0
			|| ntheader->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR_MAGIC) {
			return E_INVALIDARG;
		}

		// モジュールをデバッグ情報込みで読み込みます。
		std::string modnameA = to_string(modname);
		modbase = engine->SymLoadModule64(
			file, modnameA.c_str(), modnameA.c_str(), 0, 0);
		if (modbase == 0) {
			return HRESULT_FROM_WIN32(::GetLastError());
		}

		// モジュールの情報を取得します。
		memset(&module_info, 0, sizeof(module_info));
		module_info.SizeOfStruct = sizeof(module_info);
		if (!engine->SymGetModuleInfo64(modbase, &module_info)) {
			engine->SymUnloadModule64(modbase);
			return HRESULT_FROM_WIN32(::GetLastError());
		}

		if (modbase != ntheader->OptionalHeader.ImageBase) {
			engine->SymUnloadModule64(modbase);
			return E_UNEXPECTED;
		}

		return S_OK;
	}