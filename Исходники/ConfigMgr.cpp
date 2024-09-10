void InitLua()
{
	CHAR version[64];

	lua = luaL_newstate();
	if(lua == nullptr)
	{
		return;
	}

	luaL_openlibs(lua);

	luaL_newlib(lua, luaFuncs);
	lua_setglobal(lua, u8"crvmgr");

	//skk-version
	_snprintf_s(version, _TRUNCATE, "%s", WCTOU8(TEXTSERVICE_NAME L" " TEXTSERVICE_VER));
	lua_pushstring(lua, version);
	lua_setglobal(lua, u8"SKK_VERSION");

	//%AppData%\\CorvusSKK\\init.lua
	if(luaL_dofile(lua, WCTOU8(pathinitlua)) == LUA_OK)
	{
		return;
	}

	ZeroMemory(pathinitlua, sizeof(pathinitlua));

#ifdef _DEBUG
	//<module directory>\\init.lua
	if(GetModuleFileNameW(nullptr, pathinitlua, _countof(pathinitlua)) != 0)
	{
		WCHAR *pdir = wcsrchr(pathinitlua, L'\\');
		if(pdir != nullptr)
		{
			*(pdir + 1) = L'\0';
			wcsncat_s(pathinitlua, fninitlua, _TRUNCATE);
		}
	}
#else
	PWSTR knownfolderpath = nullptr;

	//%SystemRoot%\\IME\\IMCRVSKK\\init.lua
	if(SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Windows, KF_FLAG_DONT_VERIFY, nullptr, &knownfolderpath)))
	{
		_snwprintf_s(pathinitlua, _TRUNCATE, L"%s\\%s\\%s\\%s", knownfolderpath, L"IME", TEXTSERVICE_DIR, fninitlua);

		CoTaskMemFree(knownfolderpath);
	}
#endif

	if(luaL_dofile(lua, WCTOU8(pathinitlua)) == LUA_OK)
	{
		return;
	}

	UninitLua();
}