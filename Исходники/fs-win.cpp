/**
 * Query the properties of a mounted filesystem.
 *
 * @returns iprt status code.
 * @param   pszFsPath       Path within the mounted filesystem.
 * @param   pProperties     Where to store the properties.
 */
RTR3DECL(int) RTFsQueryProperties(const char *pszFsPath, PRTFSPROPERTIES pProperties)
{
    /*
     * Validate & get valid root path.
     */
    AssertMsgReturn(VALID_PTR(pszFsPath) && *pszFsPath, ("%p", pszFsPath), VERR_INVALID_PARAMETER);
    AssertMsgReturn(VALID_PTR(pProperties), ("%p", pProperties), VERR_INVALID_PARAMETER);
    PRTUTF16 pwszFsRoot;
    int rc = rtFsGetRoot(pszFsPath, &pwszFsRoot);
    if (RT_FAILURE(rc))
        return rc;

    /*
     * Do work.
     */
    DWORD   dwMaxName;
    DWORD   dwFlags;
    DWORD   dwSerial;
    if (GetVolumeInformationW(pwszFsRoot, NULL, 0, &dwSerial, &dwMaxName, &dwFlags, NULL, 0))
    {
        memset(pProperties, 0, sizeof(*pProperties));
        pProperties->cbMaxComponent   = dwMaxName;
        pProperties->fFileCompression = !!(dwFlags & FILE_FILE_COMPRESSION);
        pProperties->fCompressed      = !!(dwFlags & FILE_VOLUME_IS_COMPRESSED);
        pProperties->fReadOnly        = !!(dwFlags & FILE_READ_ONLY_VOLUME);
        pProperties->fSupportsUnicode = !!(dwFlags & FILE_UNICODE_ON_DISK);
        pProperties->fCaseSensitive   = false;    /* win32 is case preserving only */
        /** @todo r=bird: What about FILE_CASE_SENSITIVE_SEARCH ?  Is this set for NTFS
         *        as well perchance?  If so, better mention it instead of just setting
         *        fCaseSensitive to false. */
        pProperties->fRemote          = false;    /* no idea yet */
    }
    else
    {
        DWORD Err = GetLastError();
        rc = RTErrConvertFromWin32(Err);
        Log(("RTFsQuerySizes(%s,): GetVolumeInformation failed with lasterr %d (%Rrc)\n",
             pszFsPath, Err, rc));
    }

    RTUtf16Free(pwszFsRoot);
    return rc;
}