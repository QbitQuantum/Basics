	static void LuaGuiChooseSaveFile(lua_State *pState, void *ownerWindow, const std::string &strFilter, const std::string &initialFile, const luabind::object &initialDir, const luabind::object &dialogTitle)
	{
		boost::optional<std::string> optInitialDir, optTitle;
		char buffer[MAX_PATH], fileTitle[MAX_PATH];
		OPENFILENAMEA ofn;
		BOOL result;

		memset(&ofn, 0, sizeof(ofn));
		strcpy_s(buffer, sizeof(buffer), initialFile.c_str());

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = reinterpret_cast<HWND>(ownerWindow);
		ofn.lpstrFilter = strFilter.c_str();
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = buffer;
		ofn.nMaxFile = sizeof(buffer);
		ofn.lpstrFileTitle = fileTitle;
		ofn.nMaxFileTitle = sizeof(fileTitle);
		ofn.lpstrInitialDir = (optInitialDir = luabind::object_cast_nothrow<std::string>(initialDir))
			? optInitialDir->c_str()
			: NULL;
		ofn.lpstrTitle = (optTitle = luabind::object_cast_nothrow<std::string>(dialogTitle))
			? optTitle->c_str()
			: NULL;
		ofn.Flags = OFN_PATHMUSTEXIST;

		result = GetSaveFileNameA(&ofn);

		lua_pushboolean(pState, result);
		if (result)
		{
			lua_pushfstring(pState, "%s", buffer);
			lua_pushfstring(pState, "%s", fileTitle);
		}
		else
		{
			lua_pushnil(pState);
			lua_pushnil(pState);
		}
	}