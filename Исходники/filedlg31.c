/***********************************************************************
 *                              FD31_UpdateResult            [internal]
 *      update the displayed file name (with path)
 */
static void FD31_UpdateResult(PFD31_DATA lfs, WCHAR *tmpstr)
{
    int lenstr2;
    LPOPENFILENAMEW ofnW = lfs->ofnW;
    WCHAR tmpstr2[BUFFILE];
    WCHAR *p;

    TRACE("%s\n", debugstr_w(tmpstr));
    if(ofnW->Flags & OFN_NOVALIDATE)
        tmpstr2[0] = '\0';
    else
        GetCurrentDirectoryW(BUFFILE, tmpstr2);
    lenstr2 = strlenW(tmpstr2);
    if (lenstr2 > 3)
        tmpstr2[lenstr2++]='\\';
    lstrcpynW(tmpstr2+lenstr2, tmpstr, BUFFILE-lenstr2);
    if (ofnW->lpstrFile)
        lstrcpynW(ofnW->lpstrFile, tmpstr2, ofnW->nMaxFile);

    /* set filename offset */
    p = PathFindFileNameW(ofnW->lpstrFile);
    ofnW->nFileOffset = (p - ofnW->lpstrFile);

    /* set extension offset */
    p = PathFindExtensionW(ofnW->lpstrFile);
    ofnW->nFileExtension = (*p) ? (p - ofnW->lpstrFile) + 1 : 0;

    TRACE("file %s, file offset %d, ext offset %d\n",
          debugstr_w(ofnW->lpstrFile), ofnW->nFileOffset, ofnW->nFileExtension);

    /* update the real client structures if any */
    lfs->callbacks->UpdateResult(lfs);
}