static inline bool init_system_path(void)
{
	HRESULT hr = SHGetFolderPathA(NULL, CSIDL_SYSTEM, NULL,
			SHGFP_TYPE_CURRENT, system_path);
	if (hr != S_OK) {
		hlog("Failed to get windows system path: %08lX", hr);
		return false;
	}

	return true;
}