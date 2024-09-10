PJ_DEF(pj_status_t) pj_file_open( pj_pool_t *pool,
                                  const char *pathname, 
                                  unsigned flags,
                                  pj_oshandle_t *fd)
{
    PJ_DECL_UNICODE_TEMP_BUF(wpathname,256)
    HANDLE hFile;
    DWORD dwDesiredAccess = 0;
    DWORD dwShareMode = 0;
    DWORD dwCreationDisposition = 0;
    DWORD dwFlagsAndAttributes = 0;

    PJ_UNUSED_ARG(pool);

    PJ_ASSERT_RETURN(pathname!=NULL, PJ_EINVAL);

    if ((flags & PJ_O_WRONLY) == PJ_O_WRONLY) {
        dwDesiredAccess |= GENERIC_WRITE;
        if ((flags & PJ_O_APPEND) == PJ_O_APPEND) {
#if !defined(PJ_WIN32_WINCE) || !PJ_WIN32_WINCE
	    /* FILE_APPEND_DATA is invalid on WM2003 and WM5, but it seems
	     * to be working on WM6. All are tested on emulator though.
	     * Removing this also seem to work (i.e. data is appended), so
	     * I guess this flag is "optional".
	     * See http://trac.pjsip.org/repos/ticket/825
	     */
            dwDesiredAccess |= FILE_APPEND_DATA;
#endif
	    dwCreationDisposition |= OPEN_ALWAYS;
        } else {
            dwDesiredAccess &= ~(FILE_APPEND_DATA);
            dwCreationDisposition |= CREATE_ALWAYS;
        }
    }
    if ((flags & PJ_O_RDONLY) == PJ_O_RDONLY) {
        dwDesiredAccess |= GENERIC_READ;
        if (flags == PJ_O_RDONLY)
            dwCreationDisposition |= OPEN_EXISTING;
    }

    if (dwDesiredAccess == 0) {
        pj_assert(!"Invalid file open flags");
        return PJ_EINVAL;
    }

    dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

#ifdef PJ_WIN32_WINPHONE  
    hFile = CreateFile2(PJ_STRING_TO_NATIVE(pathname,
					    wpathname,sizeof(wpathname)), 
			dwDesiredAccess, dwShareMode, dwCreationDisposition, 
			NULL);
#else
    hFile = CreateFile(PJ_STRING_TO_NATIVE(pathname,
					   wpathname,sizeof(wpathname)), 
		       dwDesiredAccess, dwShareMode, NULL,
                       dwCreationDisposition, dwFlagsAndAttributes, NULL);
#endif

    if (hFile == INVALID_HANDLE_VALUE) {
        *fd = 0;
        return PJ_RETURN_OS_ERROR(GetLastError());
    }

    if ((flags & PJ_O_APPEND) == PJ_O_APPEND) {
	pj_status_t status;

	status = pj_file_setpos(hFile, 0, PJ_SEEK_END);
	if (status != PJ_SUCCESS) {
	    pj_file_close(hFile);
	    return status;
	}
    }

    *fd = hFile;
    return PJ_SUCCESS;
}