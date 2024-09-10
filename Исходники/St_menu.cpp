//-----------------------------------------------
void SJ_Menu_Begin( char lastState )
{
	g_timeToNextKey = 0.5f;//s_keyTime*0.5f;
	
	ZeroMemory( s_availSkins, sizeof(s_availSkins) );
	s_curSkin = 0;
	// -- Retrieve all available skins
	wchar_t path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH-1, path);
	_swprintf( g_txt, L"%s\\*", path );
#ifdef _WIN64
	PVOID OldValue = NULL;
	Wow64DisableWow64FsRedirection( &OldValue );
#endif
	WIN32_FIND_DATA ffdata;
	HANDLE hFind = FindFirstFile( g_txt, &ffdata );
	if ( hFind != INVALID_HANDLE_VALUE )
	{
		do
		{
			if ( ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				static const wchar_t* keypaths[] = { L"config.txt", L"levels", L"levels\\easy", L"levels\\medium", 
													 L"levels\\hard", L"levels\\extreme", L"sprites" };
				bool validSkin = true;
				for ( int i = 0; i < 7 && validSkin; ++i )
				{
					_swprintf( g_txt, L"%s\\%s\\%s", path, ffdata.cFileName, keypaths[i] );
					validSkin = validSkin && _waccess_s( g_txt, 0 ) == 0;
				}
				if (  validSkin && s_curSkin < MAX_AVAILSKINS )
				{
					wcscpy_s( s_availSkins[s_curSkin], ffdata.cFileName );
					if ( _wcsicmp( ffdata.cFileName, DEFAULT_SKIN ) == 0 ) 
						s_skinValue = s_curSkin;
					++s_curSkin;
				}
			}else
			{
			}
		}while ( FindNextFile(hFind,&ffdata)!=0 );
		FindClose(hFind);
	}
#ifdef _WIN64
	if ( OldValue )
		Wow64RevertWow64FsRedirection( OldValue );
#endif
	Menu_UpdateLabels();
}