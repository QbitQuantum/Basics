void handleReadingStringUpdate(HWND hwnd) {
	/* Obtain IME context */
	HIMC imc = ImmGetContext(hwnd);
	if (!imc)  return;
	wchar_t* read_str=NULL;
	HKL kbd_layout = GetKeyboardLayout(0);
	WCHAR filename[MAX_PATH + 1];
	DWORD version=0;
	HMODULE IMEFile=NULL;
	GetReadingString_funcType GetReadingString=NULL;
	if (isTSFThread(true)) {
		// Look up filename of active TIP
		if(getTIPFilename(curTSFClsID, filename, MAX_PATH)) {
			IMEFile=LoadLibrary(filename);
			if(IMEFile) {
				GetReadingString=(GetReadingString_funcType)GetProcAddress(IMEFile, "GetReadingString");
			}
		}
	}
	else if(ImmGetIMEFileNameW(kbd_layout, filename, MAX_PATH)>0) {
		IMEFile=LoadLibrary(filename);
		if(IMEFile) {
			GetReadingString=(GetReadingString_funcType)GetProcAddress(IMEFile, "GetReadingString");
		}
		if(!GetReadingString) {
			version=getIMEVersion(kbd_layout,filename);
		}
	}
	if(GetReadingString) {
		// Use GetReadingString() API if available
		UINT   len = 0;
		INT    err = 0;
		BOOL vert = FALSE;
		UINT max_len = 0;
		len = GetReadingString(imc, 0, NULL, &err, &vert, &max_len);
		if (len) {
			read_str = (WCHAR*)malloc(sizeof(WCHAR) * (len + 1));
			read_str[len] = '\0';
			GetReadingString(imc, len, read_str, &err, &vert, &max_len);
		}
	} else if(version) {
		// Read private data in IMCC
		UINT   len = 0;
		INT    err = 0;
		LPINPUTCONTEXT2 ctx = immLockIMC(imc);
		LPBYTE          priv = (LPBYTE)immLockIMCC(ctx->hPrivate);
		LPBYTE          p = 0;
		LPBYTE          str = NULL;
		switch (version) {
			case IMEID_CHT_VER42:
			case IMEID_CHT_VER43:
			case IMEID_CHT_VER44:
				p = *(LPBYTE*)(priv + 24);
				if (!p) break;
				len = *(DWORD*)(p + 7*4 + 32*4);  //m_dwInputReadStrLen
				err = *(DWORD*)(p + 8*4 + 32*4);  //m_dwErrorReadStrStart
				str =          (p + 56);
				break;

			case IMEID_CHT_VER51:  // 5.1.x.x // IME2002(w/OfficeXP)
			case IMEID_CHT_VER52:  // 5.2.x.x // (w/whistler)
			case IMEID_CHS_VER53:  // 5.3.x.x // SCIME2k or MSPY3 (w/OfficeXP and Whistler)
				p = *(LPBYTE*)(priv + 4);  // PCKeyCtrlManager
				if (!p) break;
				p = *(LPBYTE*)((LPBYTE)p + 1*4 + 5*4);  // = PCReading = &STypingInfo
				if (!p) break;
				len = *(DWORD*)(p + 1*4 + (16*2+2*4) + 5*4 + 16*2);        //m_dwDisplayStringLength;
				err = *(DWORD*)(p + 1*4 + (16*2+2*4) + 5*4 + 16*2 + 1*4);  //m_dwDisplayErrorStart;
				str =          (p + 1*4 + (16*2+2*4) + 5*4);
				break;

			case IMEID_CHS_VER42:  // 4.2.x.x // SCIME98 or MSPY2 (w/Office2k, Win2k, WinME, etc)
				p = *(LPBYTE*)(priv + 1*4 + 1*4 + 6*4);  // = PCReading = &STypintInfo
				if (!p) break;
				len = *(DWORD*)(p + 1*4 + (16*2+2*4) + 5*4 + 16*2);        //m_dwDisplayStringLength;
				err = *(DWORD*)(p + 1*4 + (16*2+2*4) + 5*4 + 16*2 + 1*4);  //m_dwDisplayErrorStart;
				str =          (p + 1*4 + (16*2+2*4) + 5*4);               //m_tszDisplayString
				break;
		}
		read_str = (WCHAR*)malloc(sizeof(WCHAR) * (len + 1));
		read_str[len] = '\0';
		memcpy(read_str, str, sizeof(WCHAR) * len);
		immUnlockIMCC(ctx->hPrivate);
		immUnlockIMC(imc);
	}
	if(IMEFile) FreeLibrary(IMEFile);
	ImmReleaseContext(hwnd, imc);
	if(read_str) {
		long len=(long)wcslen(read_str);
		if(len>1||(len==1&&read_str[0]!=L'\x3000')) {
			long cursorPos=(long)wcslen(read_str);
			nvdaControllerInternal_inputCompositionUpdate(read_str,cursorPos,cursorPos,1);
		}
		free(read_str);
	}
}