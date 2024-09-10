vxtctrlr_handle_t
vxtdev_open(char * device, unsigned int permissions)
{
    HANDLE          filehandle;
    OBJECT_ATTRIBUTES objattrs;
    NTSTATUS        status;
    IO_STATUS_BLOCK iostatus;
    UNICODE_STRING  cwsname;
    wchar_t         wszname[1024];
    wchar_t         *wcp;
    wchar_t         wc;
    const char      *cp;
    vxtctrlr_handle_t vh;
    vxt_fd_struct_t vps;
    vh = malloc(sizeof(*vh));    

    /*
     * form a Unicode pathname.  If the object directory is not
     * given (the name does not begin with / or \) then prefix
     * with the raw volume object directory.
     */
    if (device[0] != '/' && device[0] != '\\') {
        wcscpy(wszname, L"\\Device\\Vxt\\");
            wcp = wszname + wcslen(wszname);
    } else {
            wcp = wszname;
    }
    for (cp = device; (wc = (wchar_t)(uchar_t)*cp) != 0; cp++) {
            if (wc == L'/') {
                wc = L'\\';
            }
            *wcp++ = wc;
    }
    *wcp = 0;
    RtlInitUnicodeString(&cwsname, wszname);

    /*
     * open the device.  If the open fails, then return NULL and
     * set volnt_devfile_errno to indicate the error
     */
    InitializeObjectAttributes(&objattrs, &cwsname, OBJ_CASE_INSENSITIVE,
                                  NULL, NULL);
    status = NtOpenFile(&(vh->handle),
                        SYNCHRONIZE | FILE_READ_DATA | FILE_WRITE_DATA,
                        &objattrs, &iostatus,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        FILE_SYNCHRONOUS_IO_ALERT);
    if (status != STATUS_SUCCESS) {
            return VXT_INVALID_DEV_OBJ;
    }
    if (iostatus.Status != STATUS_SUCCESS || vh->handle == NULL) {
        if (vh->handle) {
            NtClose(vh->handle);
        }
        free(vh);
        return VXT_INVALID_DEV_OBJ;
    }


    vh->privdata = vh->vde = NULL;
	if(vxtdev_ioctl(vh, IOCTL_FD_OPEN, &vps)){
        NtClose(vh->handle);
        free(vh);         
        return VXT_INVALID_DEV_OBJ;
    }
    vh->privdata = vps.private_data;
    vh->vde = vps.vde;
    return vh;
}