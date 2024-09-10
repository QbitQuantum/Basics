/*
** Open file using file association if necessary.  This can be necessary if
** the file is being used by another process.
*/
int willusgui_open_file_ex(char *filename)

{
    char ext[512];
    short *extw;
    short exew[512];
    char *exename;
    char  pwd[512];
    char  cmdargs[512];
    int maxsize,status,procnum;
    HRESULT hr;
    static char *funcname="willusgui_open_file_ex";

    status=willusgui_open_file(filename);
    if (status!=-1)
        return(status);
    strncpy(&ext[1],wfile_ext(filename),510);
    ext[511]='\0';
    ext[0]='.';
    utf8_to_utf16_alloc((void **)&extw,ext);
    maxsize=511;
    hr=AssocQueryStringW(0,ASSOCSTR_EXECUTABLE,(LPCWSTR)extw,NULL,(LPWSTR)exew,(DWORD *)&maxsize);
    willus_mem_free((double **)&extw,funcname);
    if (hr==S_OK)
        utf16_to_utf8_alloc((void **)&exename,exew);
    if (hr!=S_OK || wfile_status(exename)!=1)
    {
        char *message;
        int len;
        static char *funcname="willusgui_open_file_ex";
        static int bcolors[3]= {0x6060b0,0xf0f0f0,0xf0f0f0};

        if (hr==S_OK)
            willus_mem_free((double **)&exename,funcname);
        len=strlen(filename);
        willus_mem_alloc_warn((void **)&message,len+80,funcname,10);
        sprintf(message,"Cannot find application to open %s!",filename);
        willusgui_message_box(NULL,"Error",message,"*&OK",NULL,NULL,
                              NULL,0,24,640,0xe0e0e0,bcolors,NULL,1);
        willus_mem_free((double **)&message,funcname);
        return(0);
    }
    /* Put quotes around filename -> cmdargs */
    strncpy(&cmdargs[1],filename,509);
    cmdargs[510]='\0';
    cmdargs[0]='\"';
    maxsize=strlen(cmdargs);
    cmdargs[maxsize]='\"';
    cmdargs[maxsize+1]='\0';
    /* Get working directory */
    strncpy(pwd,wfile_get_wd(),511);
    pwd[511]='\0';
    /* Make sure PWD isn't UNC -- if it is, default C:\ */
    if (pwd[0]=='\\' && pwd[1]=='\\')
        strcpy(pwd,"C:\\");
    process_launch_ex(exename,cmdargs,1,1,pwd,1,&procnum);
    willus_mem_free((double **)&exename,funcname);
    return(1);
    /*
    if (procnum>=0)
        {
        int status,exitcode;
        while ((status=process_done_ex(procnum,&exitcode))==0)
            win_sleep(10);
        if (exitcode==0)
            return(1);
        }
    */
}