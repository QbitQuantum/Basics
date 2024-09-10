CPUTResult CPUTFileSystem::ResolveAbsolutePathAndFilename(const std::string &fileName, std::string *pResolvedPathAndFilename)
{
    char pFullPathAndFilename[CPUT_MAX_PATH];
    DWORD result = GetFullPathNameA(fileName.c_str(), CPUT_MAX_PATH, pFullPathAndFilename, NULL);
    ASSERTA( 0 != result, "Error getting full path name" );
    *pResolvedPathAndFilename = pFullPathAndFilename;
    UNREFERENCED_PARAMETER(result);

    return CPUT_SUCCESS;
}