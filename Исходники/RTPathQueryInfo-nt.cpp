/**
 * Worker for RTPathQueryInfoEx and RTDirRelPathQueryInfo.
 *
 * @returns IPRT status code.
 * @param   hRootDir            The root directory that pNtName is relative to.
 * @param   pNtName             The NT path which we want to query info for.
 * @param   pObjInfo            Where to return the info.
 * @param   enmAddAttr          What additional info to get/fake.
 * @param   fFlags              Query flags (RTPATH_F_XXX).
 * @param   pszPath             The path for detecting executables and such.
 *                              Pass empty string if not applicable/available.
 */
DECLHIDDEN(int) rtPathNtQueryInfoWorker(HANDLE hRootDir, UNICODE_STRING *pNtName, PRTFSOBJINFO pObjInfo,
                                        RTFSOBJATTRADD enmAddAttr, uint32_t fFlags, const char *pszPath)
{
    /*
     * There are a three different ways of doing this:
     *   1. Use NtQueryFullAttributesFile to the get basic file info.
     *   2. Open whatever the path points to and use NtQueryInformationFile.
     *   3. Open the parent directory and use NtQueryDirectoryFile like RTDirReadEx.
     *
     * The first two options may fail with sharing violations or access denied,
     * in which case we must use the last one as fallback.
     */
    HANDLE              hFile = RTNT_INVALID_HANDLE_VALUE;
    IO_STATUS_BLOCK     Ios = RTNT_IO_STATUS_BLOCK_INITIALIZER;
    NTSTATUS            rcNt;
    OBJECT_ATTRIBUTES   ObjAttr;
    union
    {
        FILE_NETWORK_OPEN_INFORMATION   NetOpenInfo;
        FILE_ALL_INFORMATION            AllInfo;
        FILE_FS_VOLUME_INFORMATION      VolInfo;
        FILE_BOTH_DIR_INFORMATION       Both;
        FILE_ID_BOTH_DIR_INFORMATION    BothId;
        uint8_t                         abPadding[sizeof(FILE_ID_BOTH_DIR_INFORMATION) + RTPATH_MAX * sizeof(wchar_t)];
    } uBuf;

    /*
     * We can only use the first option if no additional UNIX attribs are
     * requested and it isn't a symbolic link.  NT directory object
     */
    int rc = VINF_TRY_AGAIN;
    if (   enmAddAttr != RTFSOBJATTRADD_UNIX
        && g_pfnNtQueryFullAttributesFile)
    {
        InitializeObjectAttributes(&ObjAttr, pNtName, OBJ_CASE_INSENSITIVE, hRootDir, NULL);
        rcNt = g_pfnNtQueryFullAttributesFile(&ObjAttr, &uBuf.NetOpenInfo);
        if (NT_SUCCESS(rcNt))
        {
            if (!(uBuf.NetOpenInfo.FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
            {
                pObjInfo->cbObject    = uBuf.NetOpenInfo.EndOfFile.QuadPart;
                pObjInfo->cbAllocated = uBuf.NetOpenInfo.AllocationSize.QuadPart;
                RTTimeSpecSetNtTime(&pObjInfo->BirthTime,         uBuf.NetOpenInfo.CreationTime.QuadPart);
                RTTimeSpecSetNtTime(&pObjInfo->AccessTime,        uBuf.NetOpenInfo.LastAccessTime.QuadPart);
                RTTimeSpecSetNtTime(&pObjInfo->ModificationTime,  uBuf.NetOpenInfo.LastWriteTime.QuadPart);
                RTTimeSpecSetNtTime(&pObjInfo->ChangeTime,        uBuf.NetOpenInfo.ChangeTime.QuadPart);
                pObjInfo->Attr.fMode = rtFsModeFromDos((uBuf.NetOpenInfo.FileAttributes << RTFS_DOS_SHIFT) & RTFS_DOS_MASK_NT,
                                                       pszPath, strlen(pszPath), 0 /*uReparseTag*/);
                pObjInfo->Attr.enmAdditional = enmAddAttr;

                return rtPathNtQueryInfoFillInDummyData(VINF_SUCCESS, pObjInfo, enmAddAttr);
            }
        }
        else if (   rcNt == STATUS_OBJECT_TYPE_MISMATCH
                 || rcNt == STATUS_OBJECT_NAME_INVALID
                 || rcNt == STATUS_INVALID_PARAMETER)
        {
            rc = rtPathNtQueryInfoInDirectoryObject(&ObjAttr, pObjInfo, enmAddAttr, fFlags, &uBuf, sizeof(uBuf), rcNt);
            if (RT_SUCCESS(rc))
                return rc;
        }
        else if (   rcNt != STATUS_ACCESS_DENIED
                 && rcNt != STATUS_SHARING_VIOLATION)
            rc = RTErrConvertFromNtStatus(rcNt);
        else
            RTNT_IO_STATUS_BLOCK_REINIT(&Ios);
    }

    /*
     * Try the 2nd option.  We might have to redo this if not following symbolic
     * links and the reparse point isn't a symbolic link but a mount point or similar.
     * We want to return information about the mounted root directory if we can, not
     * the directory in which it was mounted.
     */
    if (rc == VINF_TRY_AGAIN)
    {
        static int volatile g_fReparsePoints = -1;
        uint32_t            fOptions         = FILE_OPEN_FOR_BACKUP_INTENT | FILE_SYNCHRONOUS_IO_NONALERT;
        int fReparsePoints = g_fReparsePoints;
        if (fReparsePoints != 0 && !(fFlags & RTPATH_F_FOLLOW_LINK))
            fOptions |= FILE_OPEN_REPARSE_POINT;

        InitializeObjectAttributes(&ObjAttr, pNtName, OBJ_CASE_INSENSITIVE, hRootDir, NULL);
        rcNt = NtCreateFile(&hFile,
                            FILE_READ_ATTRIBUTES | SYNCHRONIZE,
                            &ObjAttr,
                            &Ios,
                            NULL /*pcbFile*/,
                            FILE_ATTRIBUTE_NORMAL,
                            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                            FILE_OPEN,
                            fOptions,
                            NULL /*pvEaBuffer*/,
                            0 /*cbEa*/);
        if (   (   rcNt == STATUS_INVALID_PARAMETER
                || rcNt == STATUS_INVALID_PARAMETER_9)
            && fReparsePoints == -1
            && (fOptions & FILE_OPEN_REPARSE_POINT))
        {
            fOptions &= ~FILE_OPEN_REPARSE_POINT;
            rcNt = NtCreateFile(&hFile,
                                FILE_READ_ATTRIBUTES | SYNCHRONIZE,
                                &ObjAttr,
                                &Ios,
                                NULL /*pcbFile*/,
                                FILE_ATTRIBUTE_NORMAL,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                FILE_OPEN,
                                fOptions,
                                NULL /*pvEaBuffer*/,
                                0 /*cbEa*/);
            if (rcNt != STATUS_INVALID_PARAMETER)
                g_fReparsePoints = fReparsePoints = 0;
        }
        if (NT_SUCCESS(rcNt))
        {
            /* Query tag information first in order to try re-open non-symlink reparse points. */
            FILE_ATTRIBUTE_TAG_INFORMATION TagInfo;
            rcNt = NtQueryInformationFile(hFile, &Ios, &TagInfo, sizeof(TagInfo), FileAttributeTagInformation);
            if (!NT_SUCCESS(rcNt))
                TagInfo.FileAttributes = TagInfo.ReparseTag = 0;
            if (   !(TagInfo.FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
                || TagInfo.ReparseTag == IO_REPARSE_TAG_SYMLINK
                || (fFlags & RTPATH_F_FOLLOW_LINK))
            { /* likely */ }
            else
            {
                /* Reparse point that isn't a symbolic link, try follow the reparsing. */
                HANDLE hFile2;
                RTNT_IO_STATUS_BLOCK_REINIT(&Ios);
                rcNt = NtCreateFile(&hFile2,
                                    FILE_READ_ATTRIBUTES | SYNCHRONIZE,
                                    &ObjAttr,
                                    &Ios,
                                    NULL /*pcbFile*/,
                                    FILE_ATTRIBUTE_NORMAL,
                                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                    FILE_OPEN,
                                    FILE_OPEN_FOR_BACKUP_INTENT | FILE_SYNCHRONOUS_IO_NONALERT,
                                    NULL /*pvEaBuffer*/,
                                    0 /*cbEa*/);
                if (NT_SUCCESS(rcNt))
                {
                    NtClose(hFile);
                    hFile = hFile2;
                    TagInfo.FileAttributes = TagInfo.ReparseTag = 0;
                }
            }

            /*
             * Get the information we need and convert it.
             */
            rc = rtPathNtQueryInfoFromHandle(hFile, &uBuf, sizeof(uBuf), pObjInfo, enmAddAttr, pszPath, TagInfo.ReparseTag);
            NtClose(hFile);
            if (RT_SUCCESS(rc))
                return rc;

            if (RT_FAILURE(rc))
                rc = VINF_TRY_AGAIN;
        }
        else if (   rcNt == STATUS_OBJECT_TYPE_MISMATCH
                 || rcNt == STATUS_OBJECT_NAME_INVALID
                 /*|| rcNt == STATUS_INVALID_PARAMETER*/)
        {
            rc = rtPathNtQueryInfoInDirectoryObject(&ObjAttr, pObjInfo, enmAddAttr, fFlags, &uBuf, sizeof(uBuf), rcNt);
            if (RT_SUCCESS(rc))
                return rc;
        }
        else if (   rcNt != STATUS_ACCESS_DENIED
                 && rcNt != STATUS_SHARING_VIOLATION)
            rc = RTErrConvertFromNtStatus(rcNt);
        else
            RTNT_IO_STATUS_BLOCK_REINIT(&Ios);
    }

    /*
     * Try the 3rd option if none of the other worked.
     * If none of the above worked, try open the directory and enumerate
     * the file we're after.  This
     */
    if (rc == VINF_TRY_AGAIN)
    {
        /* Split up the name into parent directory path and filename. */
        UNICODE_STRING NtDirName;
        UNICODE_STRING NtFilter;
        ntPathNtSplitName(pNtName, &NtDirName, &NtFilter, false /*fNoParentDirSlash*/);

        /* Try open the directory. */
        InitializeObjectAttributes(&ObjAttr, &NtDirName, OBJ_CASE_INSENSITIVE, hRootDir, NULL);
        rcNt = NtCreateFile(&hFile,
                            FILE_LIST_DIRECTORY | SYNCHRONIZE,
                            &ObjAttr,
                            &Ios,
                            NULL /*pcbFile*/,
                            FILE_ATTRIBUTE_NORMAL,
                            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                            FILE_OPEN,
                            FILE_DIRECTORY_FILE | FILE_OPEN_FOR_BACKUP_INTENT | FILE_SYNCHRONOUS_IO_NONALERT,
                            NULL /*pvEaBuffer*/,
                            0 /*cbEa*/);
        if (NT_SUCCESS(rcNt))
        {
            FILE_INFORMATION_CLASS enmInfoClass;
            if (RT_MAKE_U64(RTNtCurrentPeb()->OSMinorVersion, RTNtCurrentPeb()->OSMajorVersion) > RT_MAKE_U64(0,5) /* > W2K */)
                enmInfoClass = FileIdBothDirectoryInformation; /* Introduced in XP, from I can tell. */
            else
                enmInfoClass = FileBothDirectoryInformation;
            rcNt = NtQueryDirectoryFile(hFile,
                                        NULL /* Event */,
                                        NULL /* ApcRoutine */,
                                        NULL /* ApcContext */,
                                        &Ios,
                                        &uBuf,
                                        RT_MIN(sizeof(uBuf), 0xfff0),
                                        enmInfoClass,
                                        TRUE /*ReturnSingleEntry */,
                                        &NtFilter,
                                        FALSE /*RestartScan */);
            if (NT_SUCCESS(rcNt))
            {
                pObjInfo->cbObject    = uBuf.Both.EndOfFile.QuadPart;
                pObjInfo->cbAllocated = uBuf.Both.AllocationSize.QuadPart;

                RTTimeSpecSetNtTime(&pObjInfo->BirthTime,         uBuf.Both.CreationTime.QuadPart);
                RTTimeSpecSetNtTime(&pObjInfo->AccessTime,        uBuf.Both.LastAccessTime.QuadPart);
                RTTimeSpecSetNtTime(&pObjInfo->ModificationTime,  uBuf.Both.LastWriteTime.QuadPart);
                RTTimeSpecSetNtTime(&pObjInfo->ChangeTime,        uBuf.Both.ChangeTime.QuadPart);

                pObjInfo->Attr.fMode  = rtFsModeFromDos((uBuf.Both.FileAttributes << RTFS_DOS_SHIFT) & RTFS_DOS_MASK_NT,
                                                        pszPath, strlen(pszPath), uBuf.Both.EaSize);

                pObjInfo->Attr.enmAdditional = enmAddAttr;
                if (enmAddAttr == RTFSOBJATTRADD_UNIX)
                {
                    pObjInfo->Attr.u.Unix.uid             = ~0U;
                    pObjInfo->Attr.u.Unix.gid             = ~0U;
                    pObjInfo->Attr.u.Unix.cHardlinks      = 1;
                    pObjInfo->Attr.u.Unix.INodeIdDevice   = 0; /* below */
                    pObjInfo->Attr.u.Unix.INodeId         = enmInfoClass == FileIdBothDirectoryInformation
                                                          ? uBuf.BothId.FileId.QuadPart : 0;
                    pObjInfo->Attr.u.Unix.fFlags          = 0;
                    pObjInfo->Attr.u.Unix.GenerationId    = 0;
                    pObjInfo->Attr.u.Unix.Device          = 0;

                    /* Get the serial number. */
                    rcNt = NtQueryVolumeInformationFile(hFile, &Ios, &uBuf, RT_MIN(sizeof(uBuf), _2K),
                                                        FileFsVolumeInformation);
                    if (NT_SUCCESS(rcNt))
                        pObjInfo->Attr.u.Unix.INodeIdDevice = uBuf.VolInfo.VolumeSerialNumber;
                }

                rc = rtPathNtQueryInfoFillInDummyData(VINF_SUCCESS, pObjInfo, enmAddAttr);
            }
            else
                rc = RTErrConvertFromNtStatus(rcNt);

            NtClose(hFile);
        }
        /*
         * Quite possibly a object directory.
         */
        else if (   rcNt == STATUS_OBJECT_NAME_INVALID  /* with trailing slash */
                 || rcNt == STATUS_OBJECT_TYPE_MISMATCH /* without trailing slash */ )
        {
            InitializeObjectAttributes(&ObjAttr, pNtName, OBJ_CASE_INSENSITIVE, hRootDir, NULL);
            rc = rtPathNtQueryInfoInDirectoryObject(&ObjAttr, pObjInfo, enmAddAttr, fFlags, &uBuf, sizeof(uBuf), rcNt);
            if (RT_FAILURE(rc))
                rc = RTErrConvertFromNtStatus(rcNt);
        }
        else
            rc = RTErrConvertFromNtStatus(rcNt);
    }

    return rc;
}