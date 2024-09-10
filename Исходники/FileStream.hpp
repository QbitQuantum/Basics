bool FileStream::Open(const char* szFileName, const char* szMode, bool sharedHandle)
{
	// must not already have a handle open
	ASSERT(fs_pfh == nullptr);

#if WINDOWS
	// open file on Windows
	FILE* pfh = nullptr;
#ifndef SCRATCH_NO_UTF8
	size_t sizeFileName = strlen(szFileName) + 1;
	wchar_t* wszFileName = (wchar_t*)malloc(sizeof(wchar_t) * sizeFileName);
	mbstowcs(wszFileName, szFileName, sizeFileName);

	size_t sizeMode = strlen(szMode) + 1;
	wchar_t* wszMode = (wchar_t*)malloc(sizeof(wchar_t) * sizeMode);
	mbstowcs(wszMode, szMode, sizeMode);
#endif
	if (sharedHandle) {
#ifdef SCRATCH_NO_UTF8
		pfh = _fsopen(szFileName, szMode, _SH_DENYWR);
#else
		pfh = _wfsopen(wszFileName, wszMode, _SH_DENYWR);
#endif
	} else {
#ifdef SCRATCH_NO_UTF8
		fopen_s(&pfh, szFileName, szMode);
#else
		_wfopen_s(&pfh, wszFileName, wszMode);
#endif
	}
#ifndef SCRATCH_NO_UTF8
	free(wszFileName);
	free(wszMode);
#endif

#else
	// open file on linux
	FILE* pfh = fopen(szFileName, szMode);
#endif

	// it might not exist
	if (pfh == nullptr) {
		return false;
	}

	// remember info
	fs_strFileName = szFileName;
	fs_pfh = pfh;

	// success
	return true;
}