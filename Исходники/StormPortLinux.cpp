void GetTempFileName(const char * lpTempFolderPath, const char * lpFileName, DWORD something, char * szLFName)
{
    strcpy(szLFName, tempnam(lpTempFolderPath, lpFileName));
}