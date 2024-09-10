bool FreeTypeSysFontData::Init(LPCTSTR name, int weight, bool italic)
{
	const CGdippSettings* pSettings = CGdippSettings::GetInstance();
	void* pNameFromGDI		= NULL; // Windows 偐傜庢摼偟偨 name 僞僌偺撪梕
	void* pNameFromFreeType	= NULL; // FreeType 偐傜庢摼偟偨 name 僞僌偺撪梕
	HFONT hf = NULL;
	DWORD cbNameTable;
	DWORD cbFontData;
	int index;
	DWORD buf;
	FT_StreamRec& fsr = m_ftStream;
	m_name.assign(name);
	m_hdc = CreateCompatibleDC(NULL);
	if(m_hdc == NULL) {
		return false;
	}
	// 柤慜埲奜揔摉
	if (pSettings->FontSubstitutes() < SETTING_FONTSUBSTITUTE_ALL)
	{
		hf = CreateFont(
					12, 0, 0, 0, weight,
					italic, FALSE, FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					FONT_MAGIC_NUMBER,
					DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE,
					name);
	}
	else
		hf = CreateFont(
					12, 0, 0, 0, weight,
					italic, FALSE, FALSE,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE,
					name);

	if(hf == NULL){
		return false;
	}

	m_hOldFont = SelectFont(m_hdc, hf);
	// 僼僅儞僩僨乕僞偑摼傜傟偦偆偐僠僃僢僋
	cbNameTable = ::GetFontData(m_hdc, TVP_TT_TABLE_name, 0, NULL, 0);
	if(cbNameTable == GDI_ERROR){
		goto ERROR_Init;
	}

	pNameFromGDI		= malloc(cbNameTable);
	if (!pNameFromGDI) {
		goto ERROR_Init;
	}
	pNameFromFreeType	= malloc(cbNameTable);
	if (!pNameFromFreeType) {
		goto ERROR_Init;
	}

	//- name 僞僌偺撪梕傪儊儌儕偵撉傒崬傓
	if(GetFontData(m_hdc, TVP_TT_TABLE_name, 0, pNameFromGDI, cbNameTable) == GDI_ERROR){
		goto ERROR_Init;
	}

	// 僼僅儞僩僒僀僘庢摼張棟
	cbFontData = ::GetFontData(m_hdc, TVP_TT_TABLE_ttcf, 0, &buf, 1);
	if(cbFontData == 1){
		// TTC 僼傽僀儖偩偲巚傢傟傞
		cbFontData = ::GetFontData(m_hdc, TVP_TT_TABLE_ttcf, 0, NULL, 0);
		m_isTTC = true;
	}
	else{
		cbFontData = ::GetFontData(m_hdc, 0, 0, NULL, 0);
	}
	if(cbFontData == GDI_ERROR){
		// 僄儔乕; GetFontData 偱偼埖偊側偐偭偨
		goto ERROR_Init;
	}

	if (pSettings->UseMapping()) {
		HANDLE hmap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT | SEC_NOCACHE, 0, cbFontData, NULL);
		if (!hmap) {
			goto ERROR_Init;
		}
		m_pMapping = MapViewOfFile(hmap, FILE_MAP_ALL_ACCESS, 0, 0, cbFontData);
		m_dwSize = cbFontData;
		CloseHandle(hmap);

		if (m_pMapping) {
			::GetFontData(m_hdc, m_isTTC ? TVP_TT_TABLE_ttcf : 0, 0, m_pMapping, cbFontData);
		}
	}

	// FT_StreamRec 偺奺僼傿乕儖僪傪杽傔傞
	fsr.base				= 0;
	fsr.size				= cbFontData;
	fsr.pos					= 0;
	fsr.descriptor.pointer	= this;
	fsr.pathname.pointer	= NULL;
	fsr.read				= IoFunc;
	fsr.close				= CloseFunc;

	index = 0;
	m_locked = true;
	if(!OpenFaceByIndex(index)){
		goto ERROR_Init;
	}

	for(;;) {
		// FreeType 偐傜丄name 僞僌偺僒僀僘傪庢摼偡傞
		FT_ULong length = 0;
		FT_Error err = FT_Load_Sfnt_Table(m_ftFace, TTAG_name, 0, NULL, &length);
		if(err){
			goto ERROR_Init;
		}

		// FreeType 偐傜摼偨 name 僞僌偺挿偝傪 Windows 偐傜摼偨挿偝偲斾妑
		if(length == cbNameTable){
			// FreeType 偐傜 name 僞僌傪庢摼
			err = FT_Load_Sfnt_Table(m_ftFace, TTAG_name, 0, (unsigned char*)pNameFromFreeType, &length);
			if(err){
				goto ERROR_Init;
			}
			// FreeType 偐傜撉傒崬傫偩 name 僞僌偺撪梕偲丄Windows 偐傜撉傒崬傫偩
			// name 僞僌偺撪梕傪斾妑偡傞丅
			// 堦抳偟偰偄傟偽偦偺 index 偺僼僅儞僩傪巊偆丅
			if(!memcmp(pNameFromGDI, pNameFromFreeType, cbNameTable)){
				// 堦抳偟偨
				// face 偼奐偄偨傑傑
				break; // 儖乕僾傪敳偗傞
			}
		}

		// 堦抳偟側偐偭偨
		// 僀儞僨僢僋僗傪堦偮憹傗偟丄偦偺 face 傪奐偔
		index ++;

		if(!OpenFaceByIndex(index)){
			// 堦抳偡傞 face 偑側偄傑傑 僀儞僨僢僋僗偑斖埻傪挻偊偨偲尒傜傟傞
			// index 傪 0 偵愝掕偟偰偦偺 index 傪奐偒丄儖乕僾傪敳偗傞
			index = 0;
			if(!OpenFaceByIndex(index)){
				goto ERROR_Init;
			}
			break;
		}
	}

	free(pNameFromGDI);
	free(pNameFromFreeType);
	m_locked = false;
	return true;

ERROR_Init:
	m_locked = false;
	if (hf) {
		SelectFont(m_hdc, m_hOldFont);
		DeleteFont(hf);
		m_hOldFont = NULL;
	}
	free(pNameFromGDI);
	free(pNameFromFreeType);
	return false;
}