/*---------------------------------------------------------------------------*/
char *realpath(const char *path, char *resolved_path)
{
    char *pszFilePart;
    if (GetFullPathNameA(path, MAXPATHLEN, resolved_path, &pszFilePart)==0)
        return NULL;
    return resolved_path;
}