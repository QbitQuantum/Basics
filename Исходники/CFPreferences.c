static CFURLRef _preferencesDirectoryForUserHostSafetyLevel(CFStringRef userName, CFStringRef hostName, unsigned long safeLevel) {
    CFAllocatorRef alloc = __CFPreferencesAllocator();
#if 0

	CFURLRef url = NULL;

	UniChar szPath[MAX_PATH];
	if (S_OK == SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, (LPWSTR) szPath)) {
		CFStringRef directoryPath = CFStringCreateWithCharacters(alloc, szPath, strlen_UniChar(szPath));
		if (directoryPath) {
			CFStringRef completePath = CFStringCreateWithFormat(alloc, NULL, CFSTR("%@\\Apple\\"), directoryPath);
			if (completePath) {
				url = CFURLCreateWithFileSystemPath(alloc, completePath, kCFURLWindowsPathStyle, true);
				CFRelease(completePath);
			}
			CFRelease(directoryPath);
		}
	}

	// Can't find a better place?  Home directory then?
	if (url == NULL)
		url = CFCopyHomeDirectoryURLForUser((userName == kCFPreferencesCurrentUser) ? NULL : userName);

	return url;
 
#else
    CFURLRef  home = NULL;
    CFURLRef  url;
    int levels = 0;
    //    if (hostName != kCFPreferencesCurrentHost && hostName != kCFPreferencesAnyHost) return NULL; // Arbitrary host access not permitted
    if (userName == kCFPreferencesAnyUser) {
        if (!home) home = CFURLCreateWithFileSystemPath(alloc, CFSTR("/Library/Preferences/"), kCFURLPOSIXPathStyle, true);
        levels = 1;
        if (hostName == kCFPreferencesCurrentHost) url = home;
        else {
            url = CFURLCreateWithFileSystemPathRelativeToBase(alloc, CFSTR("Network/"), kCFURLPOSIXPathStyle, true, home);
            levels ++;
            CFRelease(home);
        }
    } else {
        home = CFCopyHomeDirectoryURLForUser((userName == kCFPreferencesCurrentUser) ? NULL : userName);
        if (home) {
            url = (safeLevel > 0) ? CFURLCreateWithFileSystemPathRelativeToBase(alloc, CFSTR("Library/Safe Preferences/"), kCFURLPOSIXPathStyle, true, home) :
            CFURLCreateWithFileSystemPathRelativeToBase(alloc, CFSTR("Library/Preferences/"), kCFURLPOSIXPathStyle, true, home);
            levels = 2;
            CFRelease(home);
            if (hostName != kCFPreferencesAnyHost) {
                home = url;
                url = CFURLCreateWithFileSystemPathRelativeToBase(alloc, CFSTR("ByHost/"), kCFURLPOSIXPathStyle, true, home);
                levels ++;
                CFRelease(home);
            }
        } else {
            url = NULL;
        }
    }
    return url;
#endif
}