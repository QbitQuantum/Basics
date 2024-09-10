int main(int argc, char **argv) {
	if (!ConfigureEnvironment()) {
		Alert(L"Mumble Launcher Error -1", L"Unable to configure environment.");
		return -1;
	}

	std::wstring versioned_root_path = GetVersionedRootPath();

	bool ok = false;
	if (!versioned_root_path.empty()) {
		if (PathFileExists(versioned_root_path.c_str())) {
			_wputenv_s(L"MUMBLE_VERSION_ROOT", versioned_root_path.c_str());
			ok = true;
		}
	}
	if (!ok) {
		_wputenv_s(L"MUMBLE_VERSION_ROOT", L"");
	}

	std::wstring abs_dll_path = GetAbsoluteMumbleAppDllPath(ok ? versioned_root_path : std::wstring());
	if (abs_dll_path.empty()) {
		Alert(L"Mumble Launcher Error -2", L"Unable to find the absolute path of mumble_app.dll.");
		return -2;
	}

	HMODULE dll = LoadLibraryExW(abs_dll_path.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (!dll) {
		Alert(L"Mumble Launcher Error -3", L"Failed to load mumble_app.dll.");
		return -3;
	}

	DLL_DEBUG_MAIN entry_point = reinterpret_cast<DLL_DEBUG_MAIN>(GetProcAddress(dll, "main"));
	if (!entry_point) {
		Alert(L"Mumble Launcher Error -4", L"Unable to find expected entry point ('main') in mumble_app.dll.");
		return -4;
	}

	int rc = entry_point(argc, argv);

	return rc;
}