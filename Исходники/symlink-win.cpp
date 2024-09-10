RTDECL(int) RTSymlinkDelete(const char *pszSymlink, uint32_t fDelete)
{
    /*
     * Convert the path.
     */
    PRTUTF16 pwszNativeSymlink;
    int rc = RTStrToUtf16(pszSymlink, &pwszNativeSymlink);
    if (RT_SUCCESS(rc))
    {
        /*
         * We have to use different APIs depending on whether this is a
         * directory or file link.  This means we're subject to one more race
         * than on posix at the moment.  We could probably avoid this though,
         * if we wanted to go talk with the native API layer below Win32...
         */
        DWORD dwAttr = GetFileAttributesW(pwszNativeSymlink);
        if (dwAttr != INVALID_FILE_ATTRIBUTES)
        {
            if (dwAttr & FILE_ATTRIBUTE_REPARSE_POINT)
            {
                BOOL fRc;
                if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
                    fRc = RemoveDirectoryW(pwszNativeSymlink);
                else
                    fRc = DeleteFileW(pwszNativeSymlink);
                if (fRc)
                    rc = VINF_SUCCESS;
                else
                    rc = RTErrConvertFromWin32(GetLastError());
            }
            else
                rc = VERR_NOT_SYMLINK;
        }
        else
            rc = RTErrConvertFromWin32(GetLastError());
        RTUtf16Free(pwszNativeSymlink);
    }

    LogFlow(("RTSymlinkDelete(%p={%s}, %#x): returns %Rrc\n", pszSymlink, pszSymlink, fDelete, rc));
    return rc;
}