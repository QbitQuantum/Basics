/*
 * Compares one file path to another.
 */
int
osys_path_cmp(const char *path1, const char *path2)
{
#if defined OSYS_DOS_OS2

    return stricmp(path1, path2);

#elif defined OSYS_WINDOWS

    return lstrcmpiA(path1, path2);

#elif OSYS_PATH_ICASE  /* generic, case-insensitive */

    return strcasecmp(path1, path2);

#else  /* generic, case-sensitive */

    return strcmp(path1, path2);

#endif
}