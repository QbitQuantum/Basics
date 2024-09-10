RTDECL(int) RTDirReadEx(PRTDIR pDir, PRTDIRENTRYEX pDirEntry, size_t *pcbDirEntry, RTFSOBJATTRADD enmAdditionalAttribs, uint32_t fFlags)
{
    /** @todo Symlinks: Find[First|Next]FileW will return info about
        the link, so RTPATH_F_FOLLOW_LINK is not handled correctly. */
    /*
     * Validate input.
     */
    if (!pDir || pDir->u32Magic != RTDIR_MAGIC)
    {
        AssertMsgFailed(("Invalid pDir=%p\n", pDir));
        return VERR_INVALID_PARAMETER;
    }
    if (!pDirEntry)
    {
        AssertMsgFailed(("Invalid pDirEntry=%p\n", pDirEntry));
        return VERR_INVALID_PARAMETER;
    }
    if (    enmAdditionalAttribs < RTFSOBJATTRADD_NOTHING
        ||  enmAdditionalAttribs > RTFSOBJATTRADD_LAST)
    {
        AssertMsgFailed(("Invalid enmAdditionalAttribs=%p\n", enmAdditionalAttribs));
        return VERR_INVALID_PARAMETER;
    }
    AssertMsgReturn(RTPATH_F_IS_VALID(fFlags, 0), ("%#x\n", fFlags), VERR_INVALID_PARAMETER);
    size_t cbDirEntry = sizeof(*pDirEntry);
    if (pcbDirEntry)
    {
        cbDirEntry = *pcbDirEntry;
        if (cbDirEntry < RT_UOFFSETOF(RTDIRENTRYEX, szName[2]))
        {
            AssertMsgFailed(("Invalid *pcbDirEntry=%d (min %d)\n", *pcbDirEntry, RT_OFFSETOF(RTDIRENTRYEX, szName[2])));
            return VERR_INVALID_PARAMETER;
        }
    }

    /*
     * Fetch data?
     */
    if (!pDir->fDataUnread)
    {
        RTStrFree(pDir->pszName);
        pDir->pszName = NULL;

        BOOL fRc = FindNextFileW(pDir->hDir, &pDir->Data);
        if (!fRc)
        {
            int iErr = GetLastError();
            if (pDir->hDir == INVALID_HANDLE_VALUE || iErr == ERROR_NO_MORE_FILES)
                return VERR_NO_MORE_FILES;
            return RTErrConvertFromWin32(iErr);
        }
    }

    /*
     * Convert the filename to UTF-8.
     */
    if (!pDir->pszName)
    {
        int rc = RTUtf16ToUtf8((PCRTUTF16)pDir->Data.cFileName, &pDir->pszName);
        if (RT_FAILURE(rc))
        {
            pDir->pszName = NULL;
            return rc;
        }
        pDir->cchName = strlen(pDir->pszName);
    }

    /*
     * Check if we've got enough space to return the data.
     */
    const char  *pszName    = pDir->pszName;
    const size_t cchName    = pDir->cchName;
    const size_t cbRequired = RT_OFFSETOF(RTDIRENTRYEX, szName[1]) + cchName;
    if (pcbDirEntry)
        *pcbDirEntry = cbRequired;
    if (cbRequired > cbDirEntry)
        return VERR_BUFFER_OVERFLOW;

    /*
     * Setup the returned data.
     */
    pDir->fDataUnread  = false;
    pDirEntry->cbName  = (uint16_t)cchName;
    Assert(pDirEntry->cbName == cchName);
    memcpy(pDirEntry->szName, pszName, cchName + 1);
    if (pDir->Data.cAlternateFileName[0])
    {
        /* copy and calc length */
        PCRTUTF16 pwszSrc = (PCRTUTF16)pDir->Data.cAlternateFileName;
        PRTUTF16  pwszDst = pDirEntry->wszShortName;
        uint32_t  off = 0;
        while (off < RT_ELEMENTS(pDirEntry->wszShortName) - 1U && pwszSrc[off])
        {
            pwszDst[off] = pwszSrc[off];
            off++;
        }
        pDirEntry->cwcShortName = (uint16_t)off;

        /* zero the rest */
        do
            pwszDst[off++] = '\0';
        while (off < RT_ELEMENTS(pDirEntry->wszShortName));
    }
    else
    {
        memset(pDirEntry->wszShortName, 0, sizeof(pDirEntry->wszShortName));
        pDirEntry->cwcShortName = 0;
    }

    pDirEntry->Info.cbObject    = ((uint64_t)pDir->Data.nFileSizeHigh << 32)
                                |  (uint64_t)pDir->Data.nFileSizeLow;
    pDirEntry->Info.cbAllocated = pDirEntry->Info.cbObject;

    Assert(sizeof(uint64_t) == sizeof(pDir->Data.ftCreationTime));
    RTTimeSpecSetNtTime(&pDirEntry->Info.BirthTime,         *(uint64_t *)&pDir->Data.ftCreationTime);
    RTTimeSpecSetNtTime(&pDirEntry->Info.AccessTime,        *(uint64_t *)&pDir->Data.ftLastAccessTime);
    RTTimeSpecSetNtTime(&pDirEntry->Info.ModificationTime,  *(uint64_t *)&pDir->Data.ftLastWriteTime);
    pDirEntry->Info.ChangeTime  = pDirEntry->Info.ModificationTime;

    pDirEntry->Info.Attr.fMode  = rtFsModeFromDos((pDir->Data.dwFileAttributes << RTFS_DOS_SHIFT) & RTFS_DOS_MASK_NT,
                                                   pszName, cchName);

    /*
     * Requested attributes (we cannot provide anything actually).
     */
    switch (enmAdditionalAttribs)
    {
        case RTFSOBJATTRADD_EASIZE:
            pDirEntry->Info.Attr.enmAdditional          = RTFSOBJATTRADD_EASIZE;
            pDirEntry->Info.Attr.u.EASize.cb            = 0;
            break;

        case RTFSOBJATTRADD_UNIX:
            pDirEntry->Info.Attr.enmAdditional          = RTFSOBJATTRADD_UNIX;
            pDirEntry->Info.Attr.u.Unix.uid             = ~0U;
            pDirEntry->Info.Attr.u.Unix.gid             = ~0U;
            pDirEntry->Info.Attr.u.Unix.cHardlinks      = 1;
            pDirEntry->Info.Attr.u.Unix.INodeIdDevice   = 0; /** @todo Use the volume serial number (see GetFileInformationByHandle). */
            pDirEntry->Info.Attr.u.Unix.INodeId         = 0; /** @todo Use the fileid (see GetFileInformationByHandle). */
            pDirEntry->Info.Attr.u.Unix.fFlags          = 0;
            pDirEntry->Info.Attr.u.Unix.GenerationId    = 0;
            pDirEntry->Info.Attr.u.Unix.Device          = 0;
            break;

        case RTFSOBJATTRADD_NOTHING:
            pDirEntry->Info.Attr.enmAdditional          = RTFSOBJATTRADD_NOTHING;
            break;

        case RTFSOBJATTRADD_UNIX_OWNER:
            pDirEntry->Info.Attr.enmAdditional          = RTFSOBJATTRADD_UNIX_OWNER;
            pDirEntry->Info.Attr.u.UnixOwner.uid        = ~0U;
            pDirEntry->Info.Attr.u.UnixOwner.szName[0]  = '\0'; /** @todo return something sensible here. */
            break;

        case RTFSOBJATTRADD_UNIX_GROUP:
            pDirEntry->Info.Attr.enmAdditional          = RTFSOBJATTRADD_UNIX_GROUP;
            pDirEntry->Info.Attr.u.UnixGroup.gid        = ~0U;
            pDirEntry->Info.Attr.u.UnixGroup.szName[0]  = '\0';
            break;

        default:
            AssertMsgFailed(("Impossible!\n"));
            return VERR_INTERNAL_ERROR;
    }

    return VINF_SUCCESS;
}