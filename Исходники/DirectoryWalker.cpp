// Build the list of files in the given folder.
BOOL BuildFilesInDir_NoHash(
    _In_ PCWSTR pszFolderpath,
    _In_opt_ PCHL_QUEUE pqDirsToTraverse,
    _Inout_ PDIRINFO* ppDirInfo)
{
    SB_ASSERT(pszFolderpath);
    SB_ASSERT(ppDirInfo);

    HANDLE hFindFile = NULL;

    loginfo(L"Building dir: %s", pszFolderpath);
    if (*ppDirInfo == NULL && FAILED(_Init(pszFolderpath, (pqDirsToTraverse != NULL), ppDirInfo)))
    {
        logerr(L"Init failed for dir: %s", pszFolderpath);
        goto error_return;
    }

    // Derefernce just to make it easier to code
    PDIRINFO pCurDirInfo = *ppDirInfo;

    // In order to list all files within the specified directory,
    // path sent to FindFirstFile must end with a "\\*"
    WCHAR szSearchpath[MAX_PATH] = L"";
    wcscpy_s(szSearchpath, ARRAYSIZE(szSearchpath), pszFolderpath);

    int nLen = wcsnlen(pszFolderpath, MAX_PATH);
    if (nLen > 2 && wcsncmp(pszFolderpath + nLen - 2, L"\\*", MAX_PATH) != 0)
    {
        PathCchCombine(szSearchpath, ARRAYSIZE(szSearchpath), pszFolderpath, L"*");
    }

    // Initialize search for files in folder
    WIN32_FIND_DATA findData;
    hFindFile = FindFirstFile(szSearchpath, &findData);
    if (hFindFile == INVALID_HANDLE_VALUE && GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        // No files found under the folder. Just return.
        return TRUE;
    }

    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        logerr(L"FindFirstFile().");
        goto error_return;
    }

    do
    {
        // Skip banned files and folders
        if (IsFileFolderBanned(findData.cFileName, ARRAYSIZE(findData.cFileName)))
        {
            continue;
        }

        szSearchpath[0] = 0;
        if (FAILED(PathCchCombine(szSearchpath, ARRAYSIZE(szSearchpath), pszFolderpath, findData.cFileName) == NULL))
        {
            logerr(L"PathCchCombine() failed for %s and %s", pszFolderpath, findData.cFileName);
            goto error_return;
        }

        PFILEINFO pFileInfo;
        if (!CreateFileInfo(szSearchpath, FALSE, &pFileInfo))
        {
            // Treat as warning and move on.
            logwarn(L"Unable to get file info for: %s", szSearchpath);
            continue;
        }

        if (pFileInfo->fIsDirectory && pqDirsToTraverse)
        {
            // If pqDirsToTraverse is not null, it means caller wants recursive directory traversal
            PDIRINFO pSubDir;
            if (FAILED(_Init(szSearchpath, TRUE, &pSubDir)))
            {
                logwarn(L"Unable to init dir info for: %s", szSearchpath);
                free(pFileInfo);
                continue;
            }

            // Insert pSubDir into the queue so that it will be traversed later
            if (FAILED(pqDirsToTraverse->Insert(pqDirsToTraverse, pSubDir, sizeof pSubDir)))
            {
                logwarn(L"Unable to add sub dir [%s] to traversal queue, cur dir: %s", findData.cFileName, pszFolderpath);
                free(pFileInfo);
                continue;
            }
            ++(pCurDirInfo->nDirs);
        }
        else
        {
            // Either this is a file or a directory but the folder must be considered as a file
            // because recursion is not enabled and we want to enable comparison of some attributes of a folder.
            // If the current file's name is already inserted, then add it to the dup within list
            BOOL fFileAdded;
            if (SUCCEEDED(CHL_DsFindHT(pCurDirInfo->phtFiles, findData.cFileName,
                StringSizeBytes(findData.cFileName), NULL, NULL, TRUE)))
            {
                fFileAdded = AddToDupWithinList(&pCurDirInfo->stDupFilesInTree, pFileInfo);
            }
            else
            {
                fFileAdded = SUCCEEDED(CHL_DsInsertHT(pCurDirInfo->phtFiles, findData.cFileName,
                    StringSizeBytes(findData.cFileName), pFileInfo, sizeof pFileInfo));
            }

            if (!fFileAdded)
            {
                logerr(L"Cannot add %s to file list: %s", (pFileInfo->fIsDirectory ? L"dir" : L"file"), findData.cFileName);
                free(pFileInfo);
            }
            else
            {
                pFileInfo->fIsDirectory ? ++(pCurDirInfo->nDirs) : ++(pCurDirInfo->nFiles);
                logdbg(L"Added %s: %s", (pFileInfo->fIsDirectory ? L"dir" : L"file"), findData.cFileName);
            }
        }
    } while (FindNextFile(hFindFile, &findData));

    if (GetLastError() != ERROR_NO_MORE_FILES)
    {
        logerr(L"Failed in enumerating files in directory: %s", pszFolderpath);
        goto error_return;
    }

    FindClose(hFindFile);
    return TRUE;

error_return:
    if (hFindFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFindFile);
    }

    if (*ppDirInfo != NULL)
    {
        DestroyDirInfo_NoHash(*ppDirInfo);
        *ppDirInfo = NULL;
    }

    return FALSE;
}