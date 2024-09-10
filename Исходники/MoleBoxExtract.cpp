DWORD WINAPI MyGetFullPathNameA(IN LPSTR lpFileName, IN DWORD nBufferLength, OUT LPTSTR lpBuffer, OUT LPSTR* lpFilePart)
{
    WCHAR szFileName[MAX_PATH], szFullName[MAX_PATH];
    ANSI_STRING aString;
    UNICODE_STRING uString;
    static Bool bFirst;

    if (!bFirst)
    {
        bFirst = True;
        MessageBoxA(0, 0, 0, 0);
    }
    RtlInitAnsiString(&aString, lpFileName);
    uString.Buffer = szFileName;
    uString.Length = 0;
    uString.MaximumLength = countof(szFileName);
    RtlAnsiStringToUnicodeString(&uString, &aString, False);
    memset(lpBuffer, 0, nBufferLength);
    nBufferLength = GetFullPathNameW(szFileName, countof(szFullName), szFullName, (LPWSTR *)lpFilePart);
    if (lpFilePart)
    {
        *lpFilePart =  *lpFilePart ? lpBuffer + (*lpFilePart - (LPSTR)szFullName) / 2 : lpBuffer;
    }
    aString.Buffer = (LPSTR)szFileName;
    aString.MaximumLength = sizeof(szFileName);
    RtlInitUnicodeString(&uString, szFullName);
    RtlUnicodeStringToAnsiString(&aString, &uString, False);
    memcpy(lpBuffer, szFileName, nBufferLength);
    if (lpFilePart && Status == UNPACKING)
    {
        lpFileName = *lpFilePart;
        memmove(lpFileName + 2, lpFileName, nBufferLength - (lpFileName - lpBuffer));
        *(LPWORD)lpFileName = '\\/';
        nBufferLength += 2;
    }

    return nBufferLength;
}