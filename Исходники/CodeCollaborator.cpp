CString CodeCollaboratorInfo::GetPathToCollabGuiExe()
{
    // this will work for X86 and X64 if the matching 'bitness' client has been installed
    PWSTR pszPath = NULL;
    if (SHGetKnownFolderPath(FOLDERID_ProgramFiles, KF_FLAG_CREATE, NULL, &pszPath) != S_OK)
        return CString();

    CString path = pszPath;
    CoTaskMemFree(pszPath);

    path += L"Collaborator Client\\ccollabgui.exe";
    if (PathFileExists(path))
        return path;

#ifdef _WIN64
    // if running on x64 OS, but installed X86 client - get try getting directory from there
    // on X86 this just returns %ProgramFiles%
    if (SHGetKnownFolderPath(FOLDERID_ProgramFilesX86, KF_FLAG_CREATE, NULL, &pszPath) != S_OK)
        return CString();

    path += L"Collaborator Client\\ccollabgui.exe";
    if (PathFileExists(path))
        return path;
#endif
    return CString();
}