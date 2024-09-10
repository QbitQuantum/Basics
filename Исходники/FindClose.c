void removeAll()
{
    RemoveDirectoryW(szDirName);
    RemoveDirectoryW(szDirName_02);

    DeleteFileW(szFindName);
    DeleteFileW(szFindName_02);
    DeleteFileW(szFindName_03);
}