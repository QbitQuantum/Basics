CFURLRef CFCopyHomeDirectoryURL(void) {
#if DEPLOYMENT_TARGET_MACOSX || DEPLOYMENT_TARGET_EMBEDDED || DEPLOYMENT_TARGET_EMBEDDED_MINI || DEPLOYMENT_TARGET_LINUX || DEPLOYMENT_TARGET_FREEBSD
    uid_t euid;
    __CFGetUGIDs(&euid, NULL);
    struct passwd *upwd = getpwuid(euid ? euid : getuid());
    return _CFCopyHomeDirURLForUser(upwd, true);
#elif DEPLOYMENT_TARGET_WINDOWS
    CFURLRef retVal = NULL;
    CFIndex len = 0;
    CFStringRef str = NULL;
   
    UniChar pathChars[MAX_PATH];
    if (S_OK == SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, (wchar_t *)pathChars)) {
        len = (CFIndex)wcslen((wchar_t *)pathChars);
        str = CFStringCreateWithCharacters(kCFAllocatorSystemDefault, pathChars, len);
        retVal = CFURLCreateWithFileSystemPath(kCFAllocatorSystemDefault, str, kCFURLWindowsPathStyle, true);
        CFRelease(str);
    }

    if (!retVal) {
        // Fall back to environment variable, but this will not be unicode compatible
        const char *cpath = __CFgetenv("HOMEPATH");
        const char *cdrive = __CFgetenv("HOMEDRIVE");
        if (cdrive && cpath) {
            char fullPath[CFMaxPathSize];
            strlcpy(fullPath, cdrive, sizeof(fullPath));
            strlcat(fullPath, cpath, sizeof(fullPath));
            str = CFStringCreateWithCString(kCFAllocatorSystemDefault, fullPath, kCFPlatformInterfaceStringEncoding);
            retVal = CFURLCreateWithFileSystemPath(kCFAllocatorSystemDefault, str, kCFURLWindowsPathStyle, true);
            CFRelease(str);
        }
    }

    if (!retVal) {
        // Last resort: We have to get "some" directory location, so fall-back to the processes current directory.
        UniChar currDir[MAX_PATH];
        DWORD dwChars = GetCurrentDirectoryW(MAX_PATH + 1, (wchar_t *)currDir);
        if (dwChars > 0) {
            len = (CFIndex)wcslen((wchar_t *)currDir);
            str = CFStringCreateWithCharacters(kCFAllocatorDefault, currDir, len);
            retVal = CFURLCreateWithFileSystemPath(NULL, str, kCFURLWindowsPathStyle, true);
            CFRelease(str);
        }
    }

    // We could do more here (as in KB Article Q101507). If that article is to be believed, we should only run into this case on Win95, or through user error.
    CFStringRef testPath = CFURLCopyFileSystemPath(retVal, kCFURLWindowsPathStyle);
    if (CFStringGetLength(testPath) == 0) {
        CFRelease(retVal);
        retVal = NULL;
    }
    if (testPath) CFRelease(testPath);

    return retVal;
#else
#error Dont know how to compute users home directories on this platform
#endif
}