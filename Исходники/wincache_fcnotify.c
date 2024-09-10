/* This method will either create a new entry altogether or modify an existing entry */
static int create_fcnotify_data(fcnotify_context * pnotify, const char * folderpath, fcnotify_value ** ppvalue)
{
    int               result    = NONFATAL;
    fcnotify_value *  pvalue    = NULL;
    alloc_context *   palloc    = NULL;
    unsigned int      pathlen   = 0;
    char *            paddr     = NULL;
    unsigned int      fshare    = 0;
    unsigned int      flags     = 0;
    unsigned int      rdcresult = 0;
    fcnotify_listen * plistener = NULL;

    dprintverbose("start create_fcnotify_data");

    _ASSERT(pnotify    != NULL);
    _ASSERT(folderpath != NULL);
    _ASSERT(ppvalue    != NULL);

    palloc = pnotify->fcalloc;
    pathlen = strlen(folderpath);

    /* Allocate memory only if its not already allocated */
    if(*ppvalue == NULL)
    {
        pvalue = (fcnotify_value *)alloc_smalloc(palloc, sizeof(fcnotify_value) + ALIGNDWORD(pathlen + 1));
        if(pvalue == NULL)
        {
            result = FATAL_OUT_OF_SMEMORY;
            goto Finished;
        }

        /* Set these to 0 only if a new structure is created */
        pvalue->reusecount  = 0;
        pvalue->folder_path = 0;
        pvalue->refcount    = 0;
        pvalue->prev_value  = 0;
        pvalue->next_value  = 0;

        /* Set folderpath only if memory is just allocated */
        paddr = (char *)(pvalue + 1);
        memcpy_s(paddr, pathlen, folderpath, pathlen);
        *(paddr + pathlen) = 0;
        pvalue->folder_path = ((char *)paddr) - pnotify->fcmemaddr;
    }
    else
    {
        pvalue = *ppvalue;
    }

    pvalue->owner_pid = pnotify->processid;
    pvalue->palivechk = GetTickCount();
    pvalue->plistener = NULL;

    pvalue->listen_time.dwHighDateTime = 0;
    pvalue->listen_time.dwLowDateTime  = 0;

    /* Allocate memory for listener locally */
    plistener = (fcnotify_listen *)alloc_pemalloc(sizeof(fcnotify_listen));
    if(plistener == NULL)
    {
        result = FATAL_OUT_OF_LMEMORY;
        goto Finished;
    }

    ZeroMemory(plistener, sizeof(fcnotify_listen));

    /* Set initial refcount and pointer to fcnotify_value */
    plistener->lrefcount  = 0;
    plistener->pfcnvalue  = pvalue;

    /* Open folder_path and attach it to completion port */
    fshare = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;
    flags = FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED;

    plistener->folder_handle = CreateFile(folderpath, FILE_LIST_DIRECTORY, fshare, NULL, OPEN_EXISTING, flags, NULL);
    if(plistener->folder_handle == INVALID_HANDLE_VALUE)
    {
        result = FATAL_FCNOTIFY_CREATEFILE;
        goto Finished;
    }

    plistener->folder_path = alloc_pestrdup(folderpath);

    if(CreateIoCompletionPort(plistener->folder_handle, pnotify->port_handle, (ULONG_PTR)0, 0) == NULL)
    {
        result = FATAL_FCNOTIFY_COMPPORT;
        goto Finished;
    }

    rdcresult = register_directory_changes(pnotify, plistener);
    if(!rdcresult)
    {
        result = FATAL_FCNOTIFY_RDCFAILURE;
        goto Finished;
    }

    pvalue->plistener = plistener;
    plistener = NULL;

    /* Update the time when the listener was set */
    GetSystemTimeAsFileTime(&pvalue->listen_time);
    
    pvalue->reusecount++;
    *ppvalue = pvalue;

Finished:

    if(FAILED(result))
    {
        dprintimportant("failure %d in create_fcnotify_data", result);
        _ASSERT(result > WARNING_COMMON_BASE);

        if(pvalue != NULL)
        {
            if(pvalue->plistener != NULL)
            {
                if(pvalue->plistener->folder_path != NULL)
                {
                    alloc_pefree(pvalue->plistener->folder_path);
                    pvalue->plistener->folder_path = NULL;
                }

                if(pvalue->plistener->folder_handle != INVALID_HANDLE_VALUE)
                {
                    CloseHandle(pvalue->plistener->folder_handle);
                    pvalue->plistener->folder_handle = INVALID_HANDLE_VALUE;
                }

                alloc_pefree(pvalue->plistener);
                pvalue->plistener = NULL;
            }

            alloc_sfree(palloc, pvalue);
            pvalue = NULL;
        }
    }

    dprintverbose("end create_fcnotify_data");

    return result;
}