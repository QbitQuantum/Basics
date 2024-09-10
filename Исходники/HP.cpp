BOOL GetKey(wchar_t** ProductKey)
{
	DWORD dwVersion = NULL;
	DWORD dwPInfo = NULL;
	DWORD dwMajorVersion = NULL;
	DWORD dwMinorVersion = NULL;
	dwVersion = GetVersion();
	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	GetProductInfo(dwMajorVersion, dwMinorVersion, 0, 0, &dwPInfo);
	switch(dwPInfo) {
	case PRODUCT_ULTIMATE:
		*ProductKey = L"MHFPT-8C8M2-V9488-FGM44-2C9T3";
		break;
	case PRODUCT_HOME_BASIC:
		*ProductKey = L"DX8R9-BVCGB-PPKRR-8J7T4-TJHTH";
		break;
	case PRODUCT_HOME_PREMIUM:
		*ProductKey = L"4FG99-BC3HD-73CQT-WMF7J-3Q6C9";
		break;
	case PRODUCT_PROFESSIONAL:
		*ProductKey = L"74T2M-DKDBC-788W3-H689G-6P6GT";
		break;
	case PRODUCT_STARTER:
		*ProductKey = L"RH98C-M9PW4-6DHR7-X99PJ-3FGDB";
		break;
	case PRODUCT_STANDARD_SERVER:
	case PRODUCT_STANDARD_SERVER_CORE:
	case PRODUCT_STANDARD_SERVER_CORE_V:
	case PRODUCT_STANDARD_SERVER_V:
		*ProductKey = L"D7TCH-6P8JP-KRG4P-VJKYY-P9GFF";
		break;
	default:
		*ProductKey = NULL;
		return FALSE;
	}
	return TRUE;
}