int __CheckProcessIdModuleInserted(unsigned int procid,const char* pPartDll)
{
    HANDLE hModSnap=INVALID_HANDLE_VALUE;
    int ret;
    BOOL bret;
    char* pCmpDllName=NULL;
    MODULEENTRY32 mentry;
    int curnum=0;
#ifdef _UNICODE
    int cmpdllnamesize=0;
#endif

try_again:
    hModSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,procid);
    if(hModSnap == INVALID_HANDLE_VALUE)
    {
        ret = LAST_ERROR_CODE();
        if(ret != ERROR_BAD_LENGTH)
        {
            //ERROR_INFO("[%d] snap module error(%d)\n",procid,ret);
            goto fail;
        }
        /*we try again for next use*/
        goto try_again;
    }

    mentry.dwSize = sizeof(mentry);

    bret = Module32First(hModSnap,&mentry);
    if(!bret)
    {
        ret = LAST_ERROR_CODE();
        ERROR_INFO("[%d] first error(%d)\n",procid,ret);
        goto fail;
    }

#ifdef _UNICODE
    ret = UnicodeToAnsi(mentry.szModule,&pCmpDllName,&cmpdllnamesize);
    if(ret < 0)
    {
        ret = LAST_ERROR_CODE();
        ERROR_INFO("[%d]:[%d] get module name error(%d)\n",procid,curnum,ret);
        goto fail;
    }
#else
    pCmpDllName = mentry.szModule;
#endif
    //DEBUG_INFO("[%d]:[%d] modname %s partdll %s\n",procid,curnum,pCmpDllName,pPartDll);
    if(_stricmp(pCmpDllName,pPartDll)==0)
    {
		DEBUG_INFO("[%d] find %s\n",procid,pPartDll);
        goto findout;
    }

    curnum ++;

    while(Module32Next(hModSnap,&mentry))
    {
#ifdef _UNICODE
        ret = UnicodeToAnsi(mentry.szModule,&pCmpDllName,&cmpdllnamesize);
        if(ret < 0)
        {
            ret = LAST_ERROR_CODE();
            ERROR_INFO("[%d]:[%d] get module name error(%d)\n",procid,curnum,ret);
            goto fail;
        }
#else
        pCmpDllName = mentry.szModule;
#endif
        //DEBUG_INFO("[%d]:[%d] modname %s partdll %s\n",procid,curnum,pCmpDllName,pPartDll);
        if(_stricmp(pCmpDllName,pPartDll)==0)
        {
			DEBUG_INFO("[%d] find %s\n",procid,pPartDll);
            goto findout;
        }
        curnum ++;
    }


#ifdef _UNICODE
    UnicodeToAnsi(NULL,&pCmpDllName,&cmpdllnamesize);
#endif
    if(hModSnap != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hModSnap);
    }
    hModSnap = INVALID_HANDLE_VALUE;
    return 0;
findout:
#ifdef _UNICODE
    UnicodeToAnsi(NULL,&pCmpDllName,&cmpdllnamesize);
#endif
    if(hModSnap != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hModSnap);
    }
    hModSnap = INVALID_HANDLE_VALUE;
    return 1;
fail:
#ifdef _UNICODE
    UnicodeToAnsi(NULL,&pCmpDllName,&cmpdllnamesize);
#endif
    if(hModSnap != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hModSnap);
    }
    hModSnap = INVALID_HANDLE_VALUE;
    SetLastError(ret);
    return -ret;
}