/***********************************************************************
 * Extract (CABINET.3)
 *
 * Extracts the contents of the cabinet file to the specified
 * destination.
 *
 * PARAMS
 *   dest      [I/O] Controls the operation of Extract.  See NOTES.
 *   szCabName [I] Filename of the cabinet to extract.
 *
 * RETURNS
 *     Success: S_OK.
 *     Failure: E_FAIL.
 *
 * NOTES
 *   The following members of the dest struct control the operation
 *   of Extract:
 *       FileSize    [O] The size of all files extracted up to CurrentFile.
 *       Error       [O] The error in case the extract operation fails.
 *       FileList    [I] A linked list of filenames.  Extract only extracts
 *                       files from the cabinet that are in this list.
 *       FileCount   [O] Contains the number of files in FileList on
 *                       completion.
 *       Operation   [I] See Operation.
 *       Destination [I] The destination directory.
 *       CurrentFile [O] The last file extracted.
 *       FilterList  [I] A linked list of files that should not be extracted.
 *
 *   Operation
 *     If Operation contains EXTRACT_FILLFILELIST, then FileList will be
 *     filled with all the files in the cabinet.  If Operation contains
 *     EXTRACT_EXTRACTFILES, then only the files in the FileList will
 *     be extracted from the cabinet.  EXTRACT_FILLFILELIST can be called
 *     by itself, but EXTRACT_EXTRACTFILES must have a valid FileList
 *     in order to succeed.  If Operation contains both EXTRACT_FILLFILELIST
 *     and EXTRACT_EXTRACTFILES, then all the files in the cabinet
 *     will be extracted.
 */
HRESULT WINAPI Extract(SESSION *dest, LPCSTR szCabName)
{
    HRESULT res = S_OK;
    HFDI hfdi;
    char *str, *end, *path = NULL, *name = NULL;

    TRACE("(%p, %s)\n", dest, debugstr_a(szCabName));

    hfdi = FDICreate(mem_alloc,
                     mem_free,
                     fdi_open,
                     fdi_read,
                     fdi_write,
                     fdi_close,
                     fdi_seek,
                     cpuUNKNOWN,
                     &dest->Error);

    if (!hfdi)
        return E_FAIL;

    if (GetFileAttributesA(dest->Destination) == INVALID_FILE_ATTRIBUTES)
    {
        res = S_OK;
        goto end;
    }

    /* split the cabinet name into path + name */
    str = HeapAlloc(GetProcessHeap(), 0, lstrlenA(szCabName)+1);
    if (!str)
    {
        res = E_OUTOFMEMORY;
        goto end;
    }
    lstrcpyA(str, szCabName);

    if ((end = strrchr(str, '\\')))
    {
        path = str;
        end++;
        name = HeapAlloc( GetProcessHeap(), 0, strlen(end) + 1 );
        if (!name)
        {
            res = E_OUTOFMEMORY;
            goto end;
        }
        strcpy( name, end );
        *end = 0;
    }
    else
    {
        name = str;
        path = NULL;
    }

    dest->FileSize = 0;

    if (!FDICopy(hfdi, name, path, 0,
         fdi_notify_extract, NULL, dest))
        res = HRESULT_FROM_WIN32(GetLastError());

end:
    HeapFree(GetProcessHeap(), 0, path);
    HeapFree(GetProcessHeap(), 0, name);
    FDIDestroy(hfdi);
    return res;
}