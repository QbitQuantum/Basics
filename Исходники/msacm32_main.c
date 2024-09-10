/***********************************************************************
 *           acmGetVersion (MSACM32.@)
 */
DWORD WINAPI acmGetVersion(void)
{
    OSVERSIONINFOA version;

    version.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    if (!GetVersionExA( &version ))
	return 0x04030000;

    switch (version.dwPlatformId) {
    case VER_PLATFORM_WIN32_NT:
	return 0x04000565; /* 4.0.1381 */
    case VER_PLATFORM_WIN32s:
	return 0x02010000; /* 2.1 */
    default:
        FIXME("%x not supported\n", version.dwPlatformId);
        /* fall through */
    case VER_PLATFORM_WIN32_WINDOWS:
	return 0x04030000; /* 4.3.0 */
    }
}