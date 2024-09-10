static void
GetFilePath(
    PWCHAR	filePath,
    ULONG	numberOfElements,
    LPCWSTR FileName)
{
    filePath[0] = 0;
    wcsncpy_s(filePath, numberOfElements, RootDirectory, wcslen(RootDirectory));
    wcsncat_s(filePath, numberOfElements, FileName, wcslen(FileName));
    RtlZeroMemory(filePath+ wcslen(filePath), (numberOfElements-wcslen(filePath)) * sizeof(WCHAR));
}