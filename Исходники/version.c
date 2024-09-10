/*
 * @implemented
 */
BOOL
WINAPI
GetVersionExA(IN LPOSVERSIONINFOA lpVersionInformation)
{
    OSVERSIONINFOEXW VersionInformation;
    LPOSVERSIONINFOEXA lpVersionInformationEx;
    UNICODE_STRING CsdVersionW;
    NTSTATUS Status;
    ANSI_STRING CsdVersionA;

    if ((lpVersionInformation->dwOSVersionInfoSize != sizeof(OSVERSIONINFOA)) &&
        (lpVersionInformation->dwOSVersionInfoSize != sizeof(OSVERSIONINFOEXA)))
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    }

    VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);

    if (!GetVersionExW((LPOSVERSIONINFOW)&VersionInformation)) return FALSE;

    /* Copy back fields that match both supported structures */
    lpVersionInformation->dwMajorVersion = VersionInformation.dwMajorVersion;
    lpVersionInformation->dwMinorVersion = VersionInformation.dwMinorVersion;
    lpVersionInformation->dwBuildNumber = VersionInformation.dwBuildNumber;
    lpVersionInformation->dwPlatformId = VersionInformation.dwPlatformId;

    if (lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA))
    {
        lpVersionInformationEx = (PVOID)lpVersionInformation;
        lpVersionInformationEx->wServicePackMajor = VersionInformation.wServicePackMajor;
        lpVersionInformationEx->wServicePackMinor = VersionInformation.wServicePackMinor;
        lpVersionInformationEx->wSuiteMask = VersionInformation.wSuiteMask;
        lpVersionInformationEx->wProductType = VersionInformation.wProductType;
        lpVersionInformationEx->wReserved = VersionInformation.wReserved;
    }

    /* Convert the CSD string */
    RtlInitEmptyAnsiString(&CsdVersionA,
                           lpVersionInformation->szCSDVersion,
                           sizeof(lpVersionInformation->szCSDVersion));
    RtlInitUnicodeString(&CsdVersionW, VersionInformation.szCSDVersion);
    Status = RtlUnicodeStringToAnsiString(&CsdVersionA, &CsdVersionW, FALSE);
    return (NT_SUCCESS(Status));
}