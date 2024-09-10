static char *
find_prog(char *origpath)
{
    wchar_t relpath[PMAX];
    wchar_t abspath[PMAX];

    if (strlen(origpath) >= PMAX)
        error("Path too long");

    MultiByteToWideChar(CP_UTF8, 0, origpath, -1, relpath, PMAX);

    if (wcsstr(relpath, LDIRSEPSTR) == NULL) {
        /* Just a base name */
	int sz;
        wchar_t *envpath;
	sz = GetEnvironmentVariableW(L"PATH", NULL, 0);
        if (sz) {	    
            /* Try to find the executable in the path */
            wchar_t dir[PMAX];
            wchar_t *beg;
            wchar_t *end;

	    HANDLE dir_handle;	        /* Handle to directory. */
	    wchar_t wildcard[PMAX];	/* Wildcard to search for. */
	    WIN32_FIND_DATAW find_data;	/* Data found by FindFirstFile() or FindNext(). */

            BOOL look_for_sep = TRUE;

	    envpath = (wchar_t *) emalloc(sz * sizeof(wchar_t*));
	    GetEnvironmentVariableW(L"PATH", envpath, sz);
	    beg = envpath;

            while (look_for_sep) {
                end = wcsstr(beg, LPATHSEPSTR);
                if (end != NULL) {
                    sz = end - beg;
                } else {
                    sz = wcslen(beg);
                    look_for_sep = FALSE;
                }
                if (sz >= PMAX) {
                    beg = end + 1;
                    continue;
                }
                wcsncpy(dir, beg, sz);
                dir[sz] = L'\0';
                beg = end + 1;

		swprintf(wildcard, PMAX, L"%s" LDIRSEPSTR L"%s",
			      dir, relpath /* basename */);
		dir_handle = FindFirstFileW(wildcard, &find_data);
		if (dir_handle == INVALID_HANDLE_VALUE) {
		    /* Try next directory in path */
		    continue;
		} else {
		    /* Wow we found the executable. */
		    wcscpy(relpath, wildcard);
		    FindClose(dir_handle);
		    look_for_sep = FALSE;
		    break;
		}
            }
	    efree(envpath);
        }
    }
    
    {
	DWORD size;
	wchar_t *absrest;
	size = GetFullPathNameW(relpath, PMAX, abspath, &absrest);
	if ((size == 0) || (size > PMAX)) {
	    /* Cannot determine absolute path to escript. Try the origin.  */
	    return strsave(origpath);
	} else {
	    char utf8abs[PMAX];
	    WideCharToMultiByte(CP_UTF8, 0, abspath, -1, utf8abs, PMAX, NULL, NULL);
	    return strsave(utf8abs);
	}
    }
}