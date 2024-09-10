void sc_GetUserAppSupportDirectory(char *str, int size)
{
	// XDG support according to http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
	const char * xdg_data_home = getenv("XDG_DATA_HOME");
	if (xdg_data_home) {
		strncpy(str, xdg_data_home, size);
		sc_AppendToPath(str, size, "SuperCollider");
		return;
	}

#if defined(_WIN32)
	ITEMIDLIST * pidl;
	char buf[MAX_PATH];
	SHGetFolderLocation(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, &pidl);
	SHGetPathFromIDList( pidl, buf );
	ILFree(pidl);
	strncpy(str, buf, size);
	sc_AppendToPath(str, size, "SuperCollider");
#else

	sc_GetUserHomeDirectory(str, size);

#if defined(SC_IPHONE)
	sc_AppendToPath(str, size, "Documents");
#elif defined(__APPLE__)
	// Get the main bundle name for the app
	sc_AppendToPath(str, size, "Library/Application Support");
	sc_AppendBundleName(str, size);
#else
	sc_AppendToPath(str, size, ".local/share/SuperCollider");
#endif

#endif
}