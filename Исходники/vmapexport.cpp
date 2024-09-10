//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
int ExtractWmo(const std::vector<std::string>& pArchiveNames)
{

    char* szListFile = "";
    char   szLocalFile[MAX_PATH] = "";
    HANDLE hMpq = "";
    BOOL bResult = FALSE;

    //const char* ParsArchiveNames[] = {"patch-2.MPQ", "patch.MPQ", "common.MPQ", "expansion.MPQ"};

    int nError = ERROR_SUCCESS;
    if(szListFile == NULL || *szListFile == 0)
        szListFile = NULL;
    //char tmp[1024];
    //for (size_t i=0; i<4; i++)
    for (size_t i=0; i<pArchiveNames.size(); i++)
    {

        //sprintf(tmp,"%s\\%s", input_path, ParsArchiveNames[i]);
        //if(!SFileOpenArchive(tmp, 0, 0, &hMpq))
        if(!SFileOpenArchive(pArchiveNames[i].c_str(), 0, 0, &hMpq))
            printf("NOT open!!! %s\n",pArchiveNames[i].c_str());

        // Copy files from archive
        if(nError == ERROR_SUCCESS)
        {
            SFILE_FIND_DATA wf;
            HANDLE hFind = SFileFindFirstFile(hMpq,"*.wmo*", &wf, szListFile);
            bResult = TRUE;

            while(hFind != NULL && bResult == TRUE)
            {
                ShowProcessedFile(wf.cFileName);
                SFileSetLocale(wf.lcLocale);
                sprintf(szLocalFile, "%s\\%s", szWorkDirWmo, GetPlainName(wf.cFileName));
                fixnamen(szLocalFile,strlen(szLocalFile));
                FILE * n;
                if ((n = fopen(szLocalFile, "rb"))== NULL)
                {
                    int p = 0;
                    //Select root wmo files
                    const char * rchr = strrchr(GetPlainName(wf.cFileName),0x5f);
                    if(rchr != NULL)
                    {
                        char cpy[4];
                        strncpy((char*)cpy,rchr,4);
                        for (int i=0;i<4;i++)
                        {
                            int m = cpy[i];
                            if(isdigit(m))
                                p++;
                        }
                    }
                    if(p != 3)
                    {
                        //printf("RootWmo!\n");
                        string s = wf.cFileName;
                        WMORoot * froot = new WMORoot(s);
                        if(!froot->open())
                        {
                            printf("Not open RootWmo!!!\n");
                            bResult = SFileFindNextFile(hFind, &wf);
                            continue;
                        }
                         FILE *output=fopen(szLocalFile,"wb");
                        froot->ConvertToVMAPRootWmo(output);
                        int Wmo_nVertices = 0;
                        if(froot->nGroups !=0)
                        {
                            for (int i=0; i<froot->nGroups; i++)
                            {
                                char temp[512];
                                strcpy(temp, wf.cFileName);
                                temp[strlen(wf.cFileName)-4] = 0;
                                char groupFileName[512];
                                sprintf(groupFileName,"%s_%03d.wmo",temp, i);
                                printf("%s\n",groupFileName);
                                //printf("GroupWmo!\n");
                                string s = groupFileName;
                                WMOGroup * fgroup = new WMOGroup(s);
                                if(!fgroup->open())
                                {
                                    printf("Not all open Group file for: %s\n",GetPlainName(wf.cFileName));
                                    bResult = SFileFindNextFile(hFind, &wf);
                                    break;
                                }
                                Wmo_nVertices += fgroup->ConvertToVMAPGroupWmo(output, preciseVectorData);
                            }
                        }
                        fseek(output, 8, SEEK_SET); // store the correct no of vertices
                        fwrite(&Wmo_nVertices,sizeof(int),1,output);
                        fclose(output);
                    }
                } else {
                    fclose(n);
                }
                wf.dwFileFlags &= ~MPQ_FILE_HAS_EXTRA;
                wf.dwFileFlags &= ~MPQ_FILE_EXISTS;
                // Find the next file
                bResult = SFileFindNextFile(hFind, &wf);
            }
            // Delete the extracted file in the case of an error
            if(nError != ERROR_SUCCESS)
                DeleteFile(szLocalFile);
            // Close the search handle
            if(hFind != NULL)
                SFileFindClose(hFind);

        }
    }
    // Close both archives
    if(hMpq != NULL)
        //SFileCloseArchive(hMpq);
        if(nError == ERROR_SUCCESS)
            printf("\nExtract wmo complete (No errors)\n");

    return nError;

}