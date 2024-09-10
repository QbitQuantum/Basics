int ExtractCurrentFile(HZIP hZip,bool bSkipPath)
{
    int r=-1;
    char filename_inzip[256];
    unz_file_info64 file_info;
    ZIPDECOMPRESSION *p=(ZIPDECOMPRESSION*)hZip;
    int err=unzGetCurrentFileInfo64(p->hZip,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
    if (err == UNZ_OK)
    {
        bool bEncrypted=((file_info.flag & 1) != 0);
        if ((bEncrypted) && (!p->bEncrypted))
        {
            ArchSetLastError(ARCH_ZIP_IS_ENCRYPTED);
            return -1;
        }

        char *lpPassword=((bEncrypted) && (p->bEncrypted)) ? p->szPassword : 0;
        int err=unzOpenCurrentFilePassword(p->hZip,lpPassword);
        if (err == UNZ_OK)
        {
            void *buf=_alloc(INT_BUF_SIZE);
            if (buf)
            {
                if (p->bExctractToMem)
                {
                    p->lpMem=VirtualAlloc(NULL,file_info.uncompressed_size,MEM_COMMIT,PAGE_READWRITE);
                    p->dwSize=file_info.uncompressed_size;
                    byte *pMem=(byte*)p->lpMem;
                    if (p->lpMem)
                    {
                        do
                        {
                            err=unzReadCurrentFile(p->hZip,pMem,INT_BUF_SIZE);
                            if (err < 0)
                            {
                                VirtualFree(p->lpMem,file_info.uncompressed_size,MEM_DECOMMIT);
                                break;
                            }
                            pMem+=err;
                        }
                        while (err > 0);
                    }
                    else
                        ArchSetLastError(ARCH_NO_MEM);

                    if (!err)
                        r=1;
                }
                else
                {
                    WCHAR *unicode_filename_inzip=OemToUnicodeEx(filename_inzip,-1),
                          file_to_store[MAX_PATH],
                          destPath[MAX_PATH],
                          *filename=unicode_filename_inzip;
                    if (bSkipPath)
                    {
                        WCHAR *p,*filename_withoutpath;
                        p=filename_withoutpath=unicode_filename_inzip;
                        while ((*p) != '\0')
                        {
                            if ((*p == '/') || (*p == '\\'))
                                filename_withoutpath=p+1;
                            p++;
                        }
                        filename=filename_withoutpath;
                    }

                    int dwLen=wsprintfW(destPath,L"%s\\%s",p->strOutputDir,filename);
                    for (int i=0; i < dwLen; i++)
                    {
                        if (destPath[i] == '/')
                            destPath[i]='\\';
                    }
                    lstrcpyW(file_to_store,destPath);
                    if (PathRemoveFileSpecW(destPath) != FALSE)
                        CreateDirectoryTree(destPath);
                    MemFree(unicode_filename_inzip);

                    HANDLE fout=CreateFileW(file_to_store,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
                    do
                    {
                        DWORD dwSize;
                        err=unzReadCurrentFile(p->hZip,buf,INT_BUF_SIZE);
                        if (err < 0)
                            break;
                        if (!WriteFile(fout,buf,err,&dwSize,0))
                        {
                            err=-1;
                            break;
                        }
                    }
                    while (err > 0);
                    SysCloseHandle(fout);
                    if (!err)
                    {
                        change_file_date(file_to_store,file_info.dosDate,file_info.tmu_date);
                        r=1;
                    }
                    else
                        DeleteFileW(file_to_store);
                }
                MemFree(buf);
            }
            unzCloseCurrentFile(p->hZip);
        }
    }
    return r;
}