std::wstring COfficeOdfFileW::GetDefWinFontDirectory()
{
	std::wstring strPath;

	wchar_t wsWinFontDir[1024] ={};
	if ( !SHGetSpecialFolderPathW( NULL, wsWinFontDir, CSIDL_FONTS, FALSE ) )
		wsWinFontDir[0] = '\0';


	strPath = std::wstring(wsWinFontDir);
	return strPath;
}