inline char* get_mapping_filename(const char *fname, char *buff)
{
    static char MEMMAP_FN_PREFIX[PATH_MAX] = "\0" ; //"c:\\temp\\" ; //"Global\\" ;
    if (!*MEMMAP_FN_PREFIX) {
        char temp[PATH_MAX] ;
        UINT len = GetSystemWindowsDirectoryA(temp, PATH_MAX) ;
        if (!len) {
            WRITE_TRACE(DBG_FATAL, "Could not get SystemWindowsDirectory, error: %d", GetLastError()) ;
            PERFC_ASSERT(false) ;
        }
        PERFC_ASSERT(len < PATH_MAX) ;
        if (temp[len-1] == '\\')
            --len ;
        strcpy(temp+len, "\\Temp\\") ;
        DWORD f_attr = GetFileAttributesA(temp) ;
        if (f_attr==INVALID_FILE_ATTRIBUTES || !( f_attr & FILE_ATTRIBUTE_DIRECTORY ))
        {
            WRITE_TRACE(DBG_FATAL, "Could not get '%s' path, error: %d", GetLastError()) ;
            PERFC_ASSERT(false) ;
        }
        // may be another thread already initialize this static value
        if (!*MEMMAP_FN_PREFIX)
            strcpy(MEMMAP_FN_PREFIX, temp) ;
    }
    static const size_t MEMMAP_FN_PREFIX_len = strlen(MEMMAP_FN_PREFIX) ;
    strcpy(buff, MEMMAP_FN_PREFIX) ;
    strcpy(buff + MEMMAP_FN_PREFIX_len, fname) ;
    return buff ;
}