// Добавляем все необходимые таблицы символов
void AddCodePages(DWORD codePages)
{
	// Добавляем стандартные таблицы символов

	uintptr_t cp_auto = CP_DEFAULT;
	if ( 0 != (codePages & ::DefaultCP) )
	{
		AddStandardCodePage(MSG(MDefaultCP), CP_DEFAULT, -1, true);
		cp_auto = CP_REDETECT;
	}
	AddStandardCodePage((codePages & ::SearchAll) ? MSG(MFindFileAllCodePages) : MSG(MEditOpenAutoDetect), cp_auto, -1, (codePages & (::SearchAll | ::Auto)) != 0);
	AddSeparator(MSG(MGetCodePageSystem));
	AddStandardCodePage(L"OEM", GetOEMCP(), -1, (codePages & ::OEM) != 0);
	AddStandardCodePage(L"ANSI", GetACP(), -1, (codePages & ::ANSI) != 0);
	AddSeparator(MSG(MGetCodePageUnicode));
	if (codePages & ::UTF7) AddStandardCodePage(L"UTF-7", CP_UTF7, -1, true); //?? не поддерживается, да и нужно ли?
	AddStandardCodePage(L"UTF-8", CP_UTF8, -1, (codePages & ::UTF8) != 0);
	AddStandardCodePage(L"UTF-16 (Little endian)", CP_UNICODE, -1, (codePages & ::UTF16LE) != 0);
	AddStandardCodePage(L"UTF-16 (Big endian)", CP_REVERSEBOM, -1, (codePages & ::UTF16BE) != 0);
	// Получаем таблицы символов установленные в системе
	allow_m2 = (codePages & ::AllowM2) != 0;
	EnumSystemCodePages((CODEPAGE_ENUMPROCW)EnumCodePagesProc, CP_INSTALLED);
}