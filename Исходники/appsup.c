BOOLEAN RemoveDirectoryPath(_In_ PWSTR DirPath)
{
    HANDLE findHandle;
    PPH_STRING findPath;
    WIN32_FIND_DATA data = { 0 };

    findPath = PhConcatStrings2(DirPath, L"\\*");

    if ((findHandle = FindFirstFile(findPath->Buffer, &data)) == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            PhDereferenceObject(findPath);
            return TRUE;
        }

        PhDereferenceObject(findPath);
        return FALSE;
    }

    do
    {
        if (PhEqualStringZ(data.cFileName, L".", TRUE) || PhEqualStringZ(data.cFileName, L"..", TRUE))
            continue;

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            PPH_STRING dirPath = PhConcatStrings(3, DirPath, L"\\", data.cFileName);

            RemoveDirectoryPath(dirPath->Buffer);
            PhDereferenceObject(dirPath);
        }
        else
        {
            PPH_STRING filePath = PhConcatStrings(3, DirPath, L"\\", data.cFileName);

            if (data.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
            {
                _wchmod(filePath->Buffer, _S_IWRITE);
            }

            SetupDeleteDirectoryFile(filePath->Buffer);
            PhDereferenceObject(filePath);
        }

    } while (FindNextFile(findHandle, &data));

    FindClose(findHandle);

    // Delete the parent directory
    RemoveDirectory(DirPath);

    PhDereferenceObject(findPath);
    return TRUE;
}