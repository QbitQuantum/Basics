INT ProcessStartupItems(VOID)
{
    /* TODO: ProcessRunKeys already checks SM_CLEANBOOT -- items prefixed with * should probably run even in safe mode */
    BOOL bNormalBoot = GetSystemMetrics(SM_CLEANBOOT) == 0; /* Perform the operations that are performed every boot */
    /* First, set the current directory to SystemRoot */
    WCHAR gen_path[MAX_PATH];
    DWORD res;

    res = GetWindowsDirectoryW(gen_path, _countof(gen_path));
    if (res == 0)
    {
        TRACE("Couldn't get the windows directory - error %lu\n", GetLastError());

        return 100;
    }

    if (!SetCurrentDirectoryW(gen_path))
    {
        TRACE("Cannot set the dir to %ls (%lu)\n", gen_path, GetLastError());

        return 100;
    }

    /* Perform the operations by order checking if policy allows it, checking if this is not Safe Mode,
     * stopping if one fails, skipping if necessary.
     */
    res = TRUE;
    /* TODO: RunOnceEx */

    if (res && (SHRestricted(REST_NOLOCALMACHINERUNONCE) == 0))
        res = ProcessRunKeys(HKEY_LOCAL_MACHINE, L"RunOnce", TRUE, TRUE);

    if (res && bNormalBoot && (SHRestricted(REST_NOLOCALMACHINERUN) == 0))
        res = ProcessRunKeys(HKEY_LOCAL_MACHINE, L"Run", FALSE, FALSE);

    if (res && bNormalBoot && (SHRestricted(REST_NOCURRENTUSERRUNONCE) == 0))
        res = ProcessRunKeys(HKEY_CURRENT_USER, L"Run", FALSE, FALSE);

    /* All users Startup folder */
    AutoStartupApplications(CSIDL_COMMON_STARTUP);

    /* Current user Startup folder */
    AutoStartupApplications(CSIDL_STARTUP);

    /* TODO: HKCU\RunOnce runs even if StartupHasBeenRun exists */
    if (res && bNormalBoot && (SHRestricted(REST_NOCURRENTUSERRUNONCE) == 0))
        res = ProcessRunKeys(HKEY_CURRENT_USER, L"RunOnce", TRUE, FALSE);

    TRACE("Operation done\n");

    return res ? 0 : 101;
}