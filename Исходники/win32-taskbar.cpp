void Win32TaskbarManager::addRecent(const Common::String &name, const Common::String &description) {
	//warning("[Win32TaskbarManager::addRecent] Adding recent list entry: %s (%s)", name.c_str(), description.c_str());

	if (_taskbar == NULL)
		return;

	// ANSI version doesn't seem to work correctly with Win7 jump lists, so explicitly use Unicode interface.
	IShellLinkW *link;

	// Get the ScummVM executable path.
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);

	// Create a shell link.
	if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC, IID_IShellLinkW, reinterpret_cast<void **> (&link)))) {
		// Convert game name and description to Unicode.
		LPWSTR game = ansiToUnicode(name.c_str());
		LPWSTR desc = ansiToUnicode(description.c_str());

		// Set link properties.
		link->SetPath(path);
		link->SetArguments(game);

		Common::String iconPath = getIconPath(name);
		if (iconPath.empty()) {
			link->SetIconLocation(path, 0); // No game-specific icon available
		} else {
			LPWSTR icon = ansiToUnicode(iconPath.c_str());

			link->SetIconLocation(icon, 0);

			delete[] icon;
		}

		// The link's display name must be set via property store.
		IPropertyStore* propStore;
		HRESULT hr = link->QueryInterface(IID_IPropertyStore, reinterpret_cast<void **> (&(propStore)));
		if (SUCCEEDED(hr)) {
			PROPVARIANT pv;
			pv.vt = VT_LPWSTR;
			pv.pwszVal = desc;

			hr = propStore->SetValue(PKEY_Title, pv);

			propStore->Commit();
			propStore->Release();
		}

		// SHAddToRecentDocs will cause the games to be added to the Recent list, allowing the user to pin them.
		SHAddToRecentDocs(SHARD_LINK, link);
		link->Release();
		delete[] game;
		delete[] desc;
	}
}