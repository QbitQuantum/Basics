int rtDirNativeOpen(PRTDIRINTERNAL pDir, uintptr_t hRelativeDir, void *pvNativeRelative)
{
    /*
     * Convert the filter to UTF-16.
     */
    int rc;
    pDir->pNtFilterStr = NULL;
    if (   pDir->cchFilter > 0
        && pDir->enmFilter == RTDIRFILTER_WINNT)
    {
        PRTUTF16 pwszTmp;
        rc = RTStrToUtf16(pDir->pszFilter, &pwszTmp);
        if (RT_FAILURE(rc))
            return rc;
        pDir->NtFilterStr.Buffer = pwszTmp;
        pDir->NtFilterStr.Length = pDir->NtFilterStr.MaximumLength = (uint16_t)(RTUtf16Len(pwszTmp) * sizeof(RTUTF16));
        pDir->pNtFilterStr = &pDir->NtFilterStr;
    }

    /*
     * Try open the directory
     */
#ifdef IPRT_WITH_NT_PATH_PASSTHRU
    bool fObjDir = false;
#endif
    if (hRelativeDir != ~(uintptr_t)0 && pvNativeRelative == NULL)
    {
        /* Caller already opened it, easy! */
        pDir->hDir = (HANDLE)hRelativeDir;
        rc = VINF_SUCCESS;
    }
    else
    {
        /*
         * If we have to check for reparse points, this gets complicated!
         */
        static int volatile g_fReparsePoints = -1;
        uint32_t            fOptions         = FILE_DIRECTORY_FILE | FILE_OPEN_FOR_BACKUP_INTENT | FILE_SYNCHRONOUS_IO_NONALERT;
        int fReparsePoints = g_fReparsePoints;
        if (   fReparsePoints != 0
            && (pDir->fFlags & RTDIR_F_NO_FOLLOW)
            && !pDir->fDirSlash)
            fOptions |= FILE_OPEN_REPARSE_POINT;

        for (;;)
        {
            if (pvNativeRelative == NULL)
                rc = RTNtPathOpenDir(pDir->pszPath,
                                     FILE_LIST_DIRECTORY | FILE_READ_ATTRIBUTES | FILE_TRAVERSE | SYNCHRONIZE,
                                     FILE_SHARE_READ | FILE_SHARE_WRITE,
                                     fOptions,
                                     OBJ_CASE_INSENSITIVE,
                                     &pDir->hDir,
#ifdef IPRT_WITH_NT_PATH_PASSTHRU
                                     &fObjDir
#else
                                     NULL
#endif
                                     );
            else
                rc = RTNtPathOpenDirEx((HANDLE)hRelativeDir,
                                       (struct _UNICODE_STRING *)pvNativeRelative,
                                       FILE_LIST_DIRECTORY | FILE_READ_ATTRIBUTES | FILE_TRAVERSE | SYNCHRONIZE,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                                       fOptions,
                                       OBJ_CASE_INSENSITIVE,
                                       &pDir->hDir,
#ifdef IPRT_WITH_NT_PATH_PASSTHRU
                                       &fObjDir
#else
                                       NULL
#endif
                                       );
            if (   !(fOptions & FILE_OPEN_REPARSE_POINT)
                || (rc != VINF_SUCCESS && rc != VERR_INVALID_PARAMETER) )
                break;
            if (rc == VINF_SUCCESS)
            {
                if (fReparsePoints == -1)
                    g_fReparsePoints = 1;

                /*
                 * We now need to check if we opened a symbolic directory link.
                 * (These can be enumerated, but contains only '.' and '..'.)
                 */
                FILE_ATTRIBUTE_TAG_INFORMATION  TagInfo = { 0, 0 };
                IO_STATUS_BLOCK                 Ios = RTNT_IO_STATUS_BLOCK_INITIALIZER;
                NTSTATUS rcNt = NtQueryInformationFile(pDir->hDir, &Ios, &TagInfo, sizeof(TagInfo), FileAttributeTagInformation);
                AssertMsg(NT_SUCCESS(rcNt), ("%#x\n", rcNt));
                if (!NT_SUCCESS(rcNt))
                    TagInfo.FileAttributes = TagInfo.ReparseTag = 0;
                if (!(TagInfo.FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
                    break;

                NtClose(pDir->hDir);
                pDir->hDir = RTNT_INVALID_HANDLE_VALUE;

                if (TagInfo.ReparseTag == IO_REPARSE_TAG_SYMLINK)
                {
                    rc = VERR_IS_A_SYMLINK;
                    break;
                }

                /* Reparse point that isn't a symbolic link, try follow the reparsing. */
            }
            else if (fReparsePoints == -1)
                g_fReparsePoints = fReparsePoints = 0;
            fOptions &= ~FILE_OPEN_REPARSE_POINT;
        }

    }
    if (RT_SUCCESS(rc))
    {
        /*
         * Init data.
         */
        pDir->fDataUnread = false; /* spelling it out */
        pDir->uDirDev     = 0;
#ifdef IPRT_WITH_NT_PATH_PASSTHRU
        if (fObjDir)
            pDir->enmInfoClass = FileMaximumInformation; /* object directory. */
#endif
    }
    return rc;
}