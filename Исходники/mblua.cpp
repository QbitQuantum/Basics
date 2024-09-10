int mesage_AddFieldBinary(lua_State* L) {
	CMessage* msg = cmessage_arg(L, "mesage_AddFieldBinary");
	CString fldName = luaL_checkstring(L, 2);
	CString path = luaL_checkstring(L, 3); 
	int err;
	char *description;

	int charsLen = ::MultiByteToWideChar(CP_UTF8, 0, path, lstrlen(path), NULL, 0);
	std::wstring characters(charsLen, '\0');
	::MultiByteToWideChar(CP_UTF8, 0, path, lstrlen(path), &characters[0], charsLen);

	int pf;
	char *b = NULL;
	err = _wsopen_s(&pf, characters.c_str(), _O_BINARY | _O_RDONLY, _SH_DENYWR, _S_IREAD);
	if (err) {
		description = "Open File error";
		goto err;
	}

	DWORD l = _filelength(pf);

	b = new char[l];


	if (l != _read(pf, b, l)) {
		err = -1;
		description = "Read File error";
		goto err;
	}
	err = _close(pf);
	if (err) {
		description = "Close File error";
		goto err;
	}
	{
		COleSafeArray arr;
		arr.Create(VT_UI1, 1, &l);

		for (DWORD i = 0; i < l; i++) {

			arr.PutElement((long*)&i, &b[i]);
		}

		msg->AddDatum(fldName, arr);
	}

err:
	if (b)
		delete []b;
	lua_pushinteger(L, err);
	if (err)
		lua_pushstring(L, description);
	else
		lua_pushinteger(L, l);
	return 2;
}