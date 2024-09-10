int __cdecl main(int argc, char *argv[])
{
    BOOL bRc = TRUE;
    BOOL bSuccess = TRUE;
    char results[40];
    FILE* resultsFile = NULL;
    int nCounter = 0;
    int i, j;
    WCHAR* wSource = NULL;
    WCHAR* wDest = NULL;
    WCHAR tempSource[] = {'t','e','m','p','k','.','t','m','p','\0'};
    WCHAR tempDest[] = {'t','e','m','p','2','.','t','m','p','\0'};
    HANDLE hFile;
    DWORD result;

    if (0 != PAL_Initialize(argc,argv))
    {
        return FAIL;
    }

    /* read in the expected results to compare with actual results */
    memset (results, 0, 20);
    resultsFile = fopen("expectedresults.txt", "r");
    if (resultsFile == NULL)
    {
        Fail("MoveFileW ERROR: Unable to open \"expectedresults.txt\"\n");
    }

    fgets(results, 20, resultsFile);
    fclose(resultsFile);

    /* clean the slate */
    removeAll();

    if (createExisting() != 0)
    {
        removeAll();
    }


    /* lpSource loop */
    for (i = 0; i < 4; i++)
    {
        /* lpDestination loop */
        for (j = 0; j < 4; j++)
        {

            wSource = convert(lpSource[i]);
            wDest = convert(lpDestination[j]);
            bRc = MoveFileW(wSource, wDest);
            free(wSource);
            free(wDest);
            if (!(
                        ((bRc == TRUE) && (results[nCounter] == '1'))
                        ||
                        ((bRc == FALSE ) && (results[nCounter] == '0'))                    )
               )
            {
                Trace("MoveFileW: FAILED: test[%d][%d]: \"%s\" -> \"%s\"\n",
                      i, j, lpSource[i], lpDestination[j]);
                bSuccess = FALSE;
            }

            /* undo the last move */
            removeAll();
            createExisting();

            nCounter++;
        }
    }

    removeAll();
    if (bSuccess == FALSE)
    {
        Fail("MoveFileW: Test Failed");
    }

    /* create the temp source file */
    hFile = CreateFileW(tempSource, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL, 0);

    if( hFile == INVALID_HANDLE_VALUE )
    {
        Fail("MoveFileW: CreateFile failed to "
             "create the file correctly.\n");
    }

    bRc = CloseHandle(hFile);
    if(!bRc)
    {
        Trace("MoveFileW: CloseHandle failed to close the "
              "handle correctly. ERROR:%u\n",GetLastError());

        /* delete the created file */
        bRc = DeleteFileW(tempSource);
        if(!bRc)
        {
            Fail("MoveFileW: DeleteFileW failed to delete the"
                 "file correctly.\n");
        }
        Fail("");
    }

    /* set the file attributes to be readonly */
    bRc = SetFileAttributesW(tempSource, FILE_ATTRIBUTE_READONLY);
    if(!bRc)
    {
        Trace("MoveFileW: SetFileAttributes failed to set file "
              "attributes correctly. GetLastError returned %u\n",GetLastError());
        /* delete the created file */
        bRc = DeleteFileW(tempSource);
        if(!bRc)
        {
            Fail("MoveFileW: DeleteFileW failed to delete the"
                 "file correctly.\n");
        }
        Fail("");
    }

    /* move the file to the new location */
    bRc = MoveFileW(tempSource, tempDest);
    if(!bRc)
    {
        /* delete the created file */
        bRc = DeleteFileW(tempSource);
        if(!bRc)
        {
            Fail("MoveFileW: DeleteFileW failed to delete the"
                 "file correctly.\n");
        }

        Fail("MoveFileW(%S, %S): GetFileAttributes "
             "failed to get the file's attributes.\n",
             tempSource, tempDest);
    }

    /* check that the newly moved file has the same file attributes
    as the original */
    result = GetFileAttributesW(tempDest);
    if(result == 0)
    {
        /* delete the created file */
        bRc = DeleteFileW(tempDest);
        if(!bRc)
        {
            Fail("MoveFileW: DeleteFileW failed to delete the"
                 "file correctly.\n");
        }

        Fail("MoveFileW: GetFileAttributes failed to get "
             "the file's attributes.\n");
    }

    if((result & FILE_ATTRIBUTE_READONLY) != FILE_ATTRIBUTE_READONLY)
    {
        /* delete the newly moved file */
        bRc = DeleteFileW(tempDest);
        if(!bRc)
        {
            Fail("MoveFileW: DeleteFileW failed to delete the"
                 "file correctly.\n");
        }

        Fail("MoveFileW: GetFileAttributes failed to get "
             "the correct file attributes.\n");
    }

    /* set the file attributes back to normal, to be deleted */
    bRc = SetFileAttributesW(tempDest, FILE_ATTRIBUTE_NORMAL);
    if(!bRc)
    {
        /* delete the newly moved file */
        bRc = DeleteFileW(tempDest);
        if(!bRc)
        {
            Fail("MoveFileW: DeleteFileW failed to delete the"
                 "file correctly.\n");
        }

        Fail("MoveFileW: SetFileAttributes failed to set "
             "file attributes correctly.\n");
    }

    /* delete the newly moved file */
    bRc = DeleteFileW(tempDest);
    if(!bRc)
    {
        Fail("MoveFileW: DeleteFileW failed to delete the"
             "file correctly.\n");
    }

    PAL_Terminate();

    return PASS;
}