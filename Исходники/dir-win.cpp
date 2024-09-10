RTDECL(int) RTDirCreate(const char *pszPath, RTFMODE fMode, uint32_t fCreate)
{
    /*
     * Validate the file mode.
     */
    int rc;
    fMode = rtFsModeNormalize(fMode, pszPath, 0);
    if (rtFsModeIsValidPermissions(fMode))
    {
        /*
         * Convert to UTF-16.
         */
        PRTUTF16 pwszString;
        rc = RTStrToUtf16(pszPath, &pwszString);
        AssertRC(rc);
        if (RT_SUCCESS(rc))
        {
            /*
             * Create the directory.
             */
            if (CreateDirectoryW((LPCWSTR)pwszString, NULL))
                rc = VINF_SUCCESS;
            else
                rc = RTErrConvertFromWin32(GetLastError());

            /*
             * Turn off indexing of directory through Windows Indexing Service
             */
            /** @todo This FILE_ATTRIBUTE_NOT_CONTENT_INDEXED hack (for .VDI files,
             *        really) may cause failures on samba shares.  That really sweet and
             *        need to be addressed differently.  We shouldn't be doing this
             *        unless the caller actually asks for it, must less returning failure,
             *        for crying out loud!  This is only important a couple of places in
             *        main, if important is the right way to put it... */
            if (   RT_SUCCESS(rc)
                && !(fCreate & RTDIRCREATE_FLAGS_NOT_CONTENT_INDEXED_DONT_SET))
            {
                if (   SetFileAttributesW((LPCWSTR)pwszString, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
                    || (fCreate & RTDIRCREATE_FLAGS_NOT_CONTENT_INDEXED_NOT_CRITICAL) )
                    rc = VINF_SUCCESS;
                else
                    rc = RTErrConvertFromWin32(GetLastError());
            }

            RTUtf16Free(pwszString);
        }
    }
    else
    {
        AssertMsgFailed(("Invalid file mode! %RTfmode\n", fMode));
        rc = VERR_INVALID_FMODE;
    }

    LogFlow(("RTDirCreate(%p:{%s}, %RTfmode): returns %Rrc\n", pszPath, pszPath, fMode, rc));
    return rc;
}