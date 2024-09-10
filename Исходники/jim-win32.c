/* win32.ShellExecute verb file args */
static int
Win32_ShellExecute(Jim_Interp *interp, int objc, Jim_Obj * const *objv)
{
    ptrdiff_t r;
    const char *verb, *file, *parm = NULL;
    char cwd[MAX_PATH + 1];

    if (objc < 3 || objc > 4) {
        Jim_WrongNumArgs(interp, 1, objv, "verb path ?parameters?");
        return JIM_ERR;
    }
    verb = Jim_String(objv[1]);
    file = Jim_String(objv[2]);
    GetCurrentDirectoryA(MAX_PATH + 1, cwd);
    if (objc == 4)
        parm = Jim_String(objv[3]);
    r = (ptrdiff_t)ShellExecuteA(NULL, verb, file, parm, cwd, SW_SHOWNORMAL);
    if (r < 33)
        Jim_SetResult(interp,
            Win32ErrorObj(interp, "ShellExecute", GetLastError()));
    return (r < 33) ? JIM_ERR : JIM_OK;
}