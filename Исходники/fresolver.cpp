FileResolver::FileResolver() {
	/* Try to detect the base path of the Mitsuba installation */
	fs::path basePath;
#if defined(__LINUX__)
	Dl_info info;

	dladdr((const void *) &dummySymbol, &info);
	if (info.dli_fname) {
		/* Try to detect a few default setups */
		if (boost::starts_with(info.dli_fname, "/usr/lib") ||
			boost::starts_with(info.dli_fname, "/lib")) {
			basePath = fs::path("/usr/share/mitsuba");
		} else if (boost::starts_with(info.dli_fname, "/usr/local/lib")) {
			basePath = fs::path("/usr/local/share/mitsuba");
		} else {
			/* This is a locally-compiled repository */
			basePath = fs::path(info.dli_fname).parent_path();
		}
	}
#elif defined(__OSX__)
	MTS_AUTORELEASE_BEGIN()
	uint32_t imageCount = _dyld_image_count();
	for (uint32_t i=0; i<imageCount; ++i) {
		const char *imageName = _dyld_get_image_name(i);
		if (boost::ends_with(imageName, "libmitsuba-core.dylib")) {
			basePath = fs::canonical(imageName).parent_path().parent_path().parent_path();
			break;
		}
	}
	MTS_AUTORELEASE_END()
	if (basePath.empty())
		Log(EError, "Could not detect the executable path!");
#elif defined(__WINDOWS__)
	std::vector<WCHAR> lpFilename(MAX_PATH);

	// Module handle to this DLL. If the function fails it sets handle to NULL.
	// In that case GetModuleFileName will get the name of the executable which
	// is acceptable soft-failure behavior.
	HMODULE handle;
	GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
	                 | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
          reinterpret_cast<LPCWSTR>(&dummySymbol), &handle);

	// Try to get the path with the default MAX_PATH length (260 chars)
	DWORD nSize = GetModuleFileNameW(handle, &lpFilename[0], MAX_PATH);

	// Adjust the buffer size in case if was too short
	while (nSize != 0 && nSize == lpFilename.size()) {
		lpFilename.resize(nSize * 2);
		nSize = GetModuleFileNameW(handle, &lpFilename[0],
			static_cast<DWORD>(lpFilename.size()));
	}

	// There is an error if and only if the function returns 0
	if (nSize != 0)
		basePath = fs::path(lpFilename).parent_path();
	else
		Log(EError, "Could not detect the executable path! (%s)", lastErrorText().c_str());
#endif
	#if BOOST_VERSION >= 104800
		m_paths.push_back(fs::canonical(basePath));
	#else
		m_paths.push_back(fs::absolute(basePath));
	#endif
	m_paths.push_back(fs::current_path());
}