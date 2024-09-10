char *Bgethomedir(void)
{
#ifdef _WIN32
	TCHAR appdata[MAX_PATH];

	if (SUCCEEDED(SHGetSpecialFolderPathA(NULL, appdata, CSIDL_APPDATA, FALSE)))
		return strdup(appdata);
	return NULL;
#elif defined __APPLE__
    
#if LOWANG_IOS
    const char* Sys_GetResourceDir(void);
	return strdup(Sys_GetResourceDir());
#else
    
	FSRef ref;
	CFStringRef str;
	CFURLRef base;
	char *s;

	if (FSFindFolder(kUserDomain, kVolumeRootFolderType, kDontCreateFolder, &ref) < 0) return NULL;
	base = CFURLCreateFromFSRef(NULL, &ref);
	if (!base) return NULL;
	str = CFURLCopyFileSystemPath(base, kCFURLPOSIXPathStyle);
	CFRelease(base);
	if (!str) return NULL;
	s = (char*)CFStringGetCStringPtr(str,CFStringGetSystemEncoding());
	if (s) s = strdup(s);
	CFRelease(str);
	return s;
#endif
#else
	char *e = getenv("HOME");
	if (!e) return NULL;
	return strdup(e);
#endif
}