/* =========================================================================
 * Handle the processing for a single directory, optionally recursing into
 *  subdirectories if needed.
 * Parameters:
 *  rootdir      [I]   The directory to search in
 *  filespec     [I]   The filespec to search for
 *  recurse      [I]   Whether to recurse (search subdirectories before
 *                          current directory)
 *  includedirs  [I]   Whether to set directory attributes as well
 *  attrib_set   [I]   Attributes to set
 *  attrib_clear [I]   Attributes to clear
 *
 * Returns TRUE if at least one file displayed / modified
 * ========================================================================= */
static BOOL ATTRIB_processdirectory(const WCHAR *rootdir, const WCHAR *filespec,
                                    BOOL recurse, BOOL includedirs,
                                    DWORD attrib_set, DWORD attrib_clear)
{
    BOOL found = FALSE;
    WCHAR buffer[MAX_PATH];
    HANDLE hff;
    WIN32_FIND_DATAW fd;
    WCHAR flags[] = {' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    static const WCHAR slashW[] = {'\\','\0'};

    WINE_TRACE("Processing dir '%s', spec '%s', %d,%x,%x\n",
               wine_dbgstr_w(rootdir), wine_dbgstr_w(filespec),
               recurse, attrib_set, attrib_clear);

    if (recurse) {

      /* Build spec to search for */
      strcpyW(buffer, rootdir);
      strcatW(buffer, starW);

      /* Search for directories in the location and recurse if necessary */
      WINE_TRACE("Searching for directories with '%s'\n", wine_dbgstr_w(buffer));
      hff = FindFirstFileW(buffer, &fd);
      if (hff != INVALID_HANDLE_VALUE) {
          do {
              const WCHAR dot[] = {'.', 0};
              const WCHAR dotdot[] = {'.', '.', 0};

              /* Only interested in directories, and not . nor .. */
              if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ||
                  !strcmpW(fd.cFileName, dot) || !strcmpW(fd.cFileName, dotdot))
                  continue;

              /* Build new root dir to go searching in */
              strcpyW(buffer, rootdir);
              strcatW(buffer, fd.cFileName);
              strcatW(buffer, slashW);
              ATTRIB_processdirectory(buffer, filespec, recurse, includedirs,
                                      attrib_set, attrib_clear);

          } while (FindNextFileW(hff, &fd) != 0);
      }
      FindClose (hff);
    }

    /* Build spec to search for */
    strcpyW(buffer, rootdir);
    strcatW(buffer, filespec);
    WINE_TRACE("Searching for files as '%s'\n", wine_dbgstr_w(buffer));

    /* Search for files in the location with the filespec supplied */
    hff = FindFirstFileW(buffer, &fd);
    if (hff != INVALID_HANDLE_VALUE) {
        do {
            const WCHAR dot[] = {'.', 0};
            const WCHAR dotdot[] = {'.', '.', 0};
            DWORD count;
            WINE_TRACE("Found '%s'\n", wine_dbgstr_w(fd.cFileName));

            if (!strcmpW(fd.cFileName, dot) || !strcmpW(fd.cFileName, dotdot))
                continue;

            if (!includedirs && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
              continue;

            if (attrib_set || attrib_clear) {
                fd.dwFileAttributes &= ~attrib_clear;
                fd.dwFileAttributes |= attrib_set;
                if (!fd.dwFileAttributes)
                    fd.dwFileAttributes |= FILE_ATTRIBUTE_NORMAL;
                strcpyW(buffer, rootdir);
                strcatW(buffer, fd.cFileName);
                SetFileAttributesW(buffer, fd.dwFileAttributes);
                found = TRUE;
            } else {
                static const WCHAR fmt[] = {'%','1',' ',' ',' ',' ',' ','%','2','\n','\0'};
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
                    flags[4] = 'H';
                }
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) {
                    flags[1] = 'S';
                }
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
                    flags[0] = 'A';
                }
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
                    flags[5] = 'R';
                }
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY) {
                    flags[6] = 'T';
                }
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) {
                    flags[7] = 'C';
                }
                strcpyW(buffer, rootdir);
                strcatW(buffer, fd.cFileName);
                ATTRIB_wprintf(fmt, flags, buffer);
                for (count = 0; count < (sizeof(flags)/sizeof(WCHAR) - 1); count++) flags[count] = ' ';
                found = TRUE;
            }
        } while (FindNextFileW(hff, &fd) != 0);
    }
    FindClose (hff);
    return found;
}