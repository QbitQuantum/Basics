/* Returns the working directory for the given drive, or NULL */
WCHAR*
currentDir(int di) {
    UINT dt;
    WCHAR root[4];
    // verify drive is valid as _wgetdcwd in the VC++ 2010 runtime
    // library does not handle invalid drives.
    root[0] = L'A' + (WCHAR)(di - 1);
    root[1] = L':';
    root[2] = L'\\';
    root[3] = L'\0';
    dt = GetDriveTypeW(root);
    if (dt == DRIVE_UNKNOWN || dt == DRIVE_NO_ROOT_DIR) {
        return NULL;
    } else {
        return _wgetdcwd(di, NULL, MAX_PATH);
    }
}