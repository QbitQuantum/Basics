static int shell_execute_ex(DWORD mask, LPCSTR operation, LPCSTR file,
                            LPCSTR parameters, LPCSTR directory)
{
    SHELLEXECUTEINFO sei;
    BOOL success;
    int rc;

    strcpy(shell_call, "ShellExecuteEx(");
    strcat_param(shell_call, operation);
    strcat(shell_call, ", ");
    strcat_param(shell_call, file);
    strcat(shell_call, ", ");
    strcat_param(shell_call, parameters);
    strcat(shell_call, ", ");
    strcat_param(shell_call, directory);
    strcat(shell_call, ")");
    if (winetest_debug > 1)
        trace("%s\n", shell_call);

    sei.cbSize=sizeof(sei);
    sei.fMask=SEE_MASK_NOCLOSEPROCESS | mask;
    sei.hwnd=NULL;
    sei.lpVerb=operation;
    sei.lpFile=file;
    sei.lpParameters=parameters;
    sei.lpDirectory=directory;
    sei.nShow=SW_SHOWNORMAL;
    sei.hInstApp=NULL; /* Out */
    sei.lpIDList=NULL;
    sei.lpClass=NULL;
    sei.hkeyClass=NULL;
    sei.dwHotKey=0;
    U(sei).hIcon=NULL;
    sei.hProcess=NULL; /* Out */

    DeleteFile(child_file);
    SetLastError(0xcafebabe);
    success=ShellExecuteEx(&sei);
    rc=(int)sei.hInstApp;
    ok((success && rc >= 32) || (!success && rc < 32),
       "%s rc=%d and hInstApp=%d is not allowed\n", shell_call, success, rc);

    if (rc>=32)
    {
        int wait_rc;
        if (sei.hProcess!=NULL)
        {
            wait_rc=WaitForSingleObject(sei.hProcess, 5000);
            ok(wait_rc==WAIT_OBJECT_0, "WaitForSingleObject(hProcess) returned %d\n", wait_rc);
        }
        wait_rc=WaitForSingleObject(hEvent, 5000);
        ok(wait_rc==WAIT_OBJECT_0, "WaitForSingleObject returned %d\n", wait_rc);
    }
    /* The child process may have changed the result file, so let profile
     * functions know about it
     */
    WritePrivateProfileStringA(NULL, NULL, NULL, child_file);
    if (rc>=32)
        dump_child();

    return rc;
}