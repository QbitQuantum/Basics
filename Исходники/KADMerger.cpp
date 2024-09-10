int Remerge()
{
    int i;
    char pszInstallDir[MAX_PATH];
    char pszKadName[MAX_PATH];
    char pszOrigKadName[MAX_PATH];
    char pszBackKadName[MAX_PATH];
    char pszAddKAD[MAX_PATH];
    char pszAddKADFullPath[MAX_PATH];
    char pszLogFile[MAX_PATH];
    char pszFindFilePattern[MAX_PATH];
    BOOL bError = FALSE;

    // hack fill with something: KAD merge Dll test for strlen of parameter
    for(i=0; i<MAX_PATH; i++)
    {
        pszInstallDir[i] = 1;
    }
    pszInstallDir[MAX_PATH-1] = 0;
    if (Get4CPath(pszInstallDir)!=TRUE)
    {
        printf("Error: Looking up ATCMControl installation path!\n");
        return -1;
    }


    // ************************ 4ceng.kad  *************************
    strcpy(pszOrigKadName, pszInstallDir);
    strcat(pszOrigKadName, "Engineering\\bin\\4ceng.kad");
    
    strcpy(pszBackKadName, pszOrigKadName);
    strcat(pszBackKadName, ".back");

    DeleteFile(pszBackKadName);
    if (!MoveFile(pszOrigKadName, pszBackKadName))
    {
        printf("Could not create backup of 4ceng.kad\n");
    }

    printf("Merging 4ceng.kad\n");

    strcpy(pszKadName, "Engineering\\bin\\4ceng.kad");
    strcpy(pszLogFile, "KadMerge.log");


    HANDLE hFind;
    WIN32_FIND_DATA findFileData;
    BOOL bFound = TRUE;

    strcpy(pszFindFilePattern, pszInstallDir);
    strcat(pszFindFilePattern, "Engineering\\bin\\*_4ceng.kad");


    // start with Kernel_IEC_4ceng.kad and skip this later
    strcpy(pszAddKAD, "Kernel_IEC_4ceng.kad");
    strcpy(pszAddKADFullPath, pszInstallDir);
    strcat(pszAddKADFullPath, "Engineering\\bin\\");
    strcat(pszAddKADFullPath, pszAddKAD);
    printf("Merging KAD: %s\n", pszAddKAD);
    if (MergeKAD_KnieFK(pszInstallDir, 
                         pszKadName, 
                         pszAddKADFullPath, 
                         TRUE, 
                         pszLogFile, 
                         FALSE)  != TRUE)
    {
        printf("Error: Merging KAD %s!\n", pszAddKAD);
        bError = TRUE;
    }
  
    hFind = FindFirstFile(pszFindFilePattern, &findFileData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        while (bFound)
        {
            strcpy(pszAddKAD, findFileData.cFileName);

            if (stricmp(pszAddKAD, "Kernel_IEC_4ceng.kad")!=0)
            {
                strcpy(pszAddKADFullPath, pszInstallDir);
                strcat(pszAddKADFullPath, "Engineering\\bin\\");
                strcat(pszAddKADFullPath, pszAddKAD);
                printf("Merging KAD: %s\n", pszAddKAD);
                if (MergeKAD_KnieFK(pszInstallDir, 
                                     pszKadName, 
                                     pszAddKADFullPath, 
                                     TRUE, 
                                     pszLogFile, 
                                     FALSE)  != TRUE)
                {
                    printf("Error: Merging KAD %s!\n", pszAddKAD);
                    bError = TRUE;
                }
            }
            bFound = FindNextFile(hFind, &findFileData);
        }
        FindClose(hFind);
    }



    // ************************ 4cg.kad  *************************
    strcpy(pszOrigKadName, pszInstallDir);
    strcat(pszOrigKadName, "Engineering\\bin\\4cg.kad");
    
    strcpy(pszBackKadName, pszOrigKadName);
    strcat(pszBackKadName, ".back");

    DeleteFile(pszBackKadName);
    if (!MoveFile(pszOrigKadName, pszBackKadName))
    {
        printf("Could not create backup of 4ceng.kad\n");
    }

    printf("\nRemerging 4cg.kad\n");

    strcpy(pszKadName, "Engineering\\bin\\4cg.kad");
    strcpy(pszLogFile, "KadMerge_CG.log");


    bFound = TRUE;

    strcpy(pszFindFilePattern, pszInstallDir);
    strcat(pszFindFilePattern, "Engineering\\bin\\*_4cg.kad");
  
    hFind = FindFirstFile(pszFindFilePattern, &findFileData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        while (bFound)
        {
            strcpy(pszAddKAD, findFileData.cFileName);

            strcpy(pszAddKADFullPath, pszInstallDir);
            strcat(pszAddKADFullPath, "Engineering\\bin\\");
            strcat(pszAddKADFullPath, pszAddKAD);
            printf("Merging KAD: %s\n", pszAddKAD);
            if (MergeKAD_KnieFK(pszInstallDir, 
                                 pszKadName, 
                                 pszAddKADFullPath, 
                                 TRUE, 
                                 pszLogFile, 
                                 FALSE)  != TRUE)
            {
                printf("Error: Merging KAD %s!\n", pszAddKAD);
                bError = TRUE;
            }
            bFound = FindNextFile(hFind, &findFileData);
        }
        FindClose(hFind);
    }

    printf("\n");
    if (bError)
    {
        printf("*************\n"
               " Errors during KAD remerging,\n"
               " the old KAD files are still available (4cg|4ceng).kad.back,\n"
               " please rename to original file names.\n\n");
    }
    else
    {
        printf("KADs successfully remerged!\n");
    }
    printf("\n");

    return 0;
}