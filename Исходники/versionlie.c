BOOL FakeVersion(LPOSVERSIONINFOEXA pResult, VersionLieInfo* pFake)
{
    if (pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA) || pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA) ||
        pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW) || pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOW))
    {
        pResult->dwMajorVersion = pFake->dwMajorVersion;
        pResult->dwMinorVersion = pFake->dwMinorVersion;
        pResult->dwBuildNumber = pFake->dwBuildNumber;
        pResult->dwPlatformId = pFake->dwPlatformId;
        if (pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA) || pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA))
        {
            if (FAILED(StringCbCopyA(pResult->szCSDVersion, sizeof(pResult->szCSDVersion), pFake->szCSDVersionA)))
                return FALSE;
            if (pResult->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA) && pFake->dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
            {
                pResult->wServicePackMajor = pFake->wServicePackMajor;
                pResult->wServicePackMinor = pFake->wServicePackMinor;
            }
        }
        else
        {
            LPOSVERSIONINFOEXW pResultW = (LPOSVERSIONINFOEXW)pResult;
            if (FAILED(StringCbCopyW(pResultW->szCSDVersion, sizeof(pResultW->szCSDVersion), pFake->szCSDVersionW)))
                return FALSE;
            if (pResultW->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW) && pFake->dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
            {
                pResultW->wServicePackMajor = pFake->wServicePackMajor;
                pResultW->wServicePackMinor = pFake->wServicePackMinor;
            }
        }
        return TRUE;
    }
    return FALSE;
}