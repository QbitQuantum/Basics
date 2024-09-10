BOOL ShellCache::IsPathAllowed(LPCTSTR path)
{
    ValidatePathFilter();
    Locker lock(m_critSec);
    svn_tristate_t allowed = pathFilter.IsPathAllowed (path);
    if (allowed != svn_tristate_unknown)
        return allowed == svn_tristate_true ? TRUE : FALSE;

    UINT drivetype = 0;
    int drivenumber = PathGetDriveNumber(path);
    if ((drivenumber >=0)&&(drivenumber < 25))
    {
        drivetype = drivetypecache[drivenumber];
        if ((drivetype == -1)||((GetTickCount64() - drivetypeticker)>DRIVETYPETIMEOUT))
        {
            if ((DWORD(drivefloppy) == 0)&&((drivenumber == 0)||(drivenumber == 1)))
                drivetypecache[drivenumber] = DRIVE_REMOVABLE;
            else
            {
                drivetypeticker = GetTickCount64();
                TCHAR pathbuf[MAX_PATH + 4] = { 0 };      // MAX_PATH ok here. PathStripToRoot works with partial paths too.
                wcsncpy_s(pathbuf, path, _countof(pathbuf)-1);
                PathStripToRoot(pathbuf);
                PathAddBackslash(pathbuf);
                CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L": GetDriveType for %s, Drive %d\n", pathbuf, drivenumber);
                drivetype = GetDriveType(pathbuf);
                drivetypecache[drivenumber] = drivetype;
            }
        }
    }
    else
    {
        TCHAR pathbuf[MAX_PATH + 4] = { 0 };      // MAX_PATH ok here. PathIsUNCServer works with partial paths too.
        wcsncpy_s(pathbuf, path, _countof(pathbuf)-1);
        if (PathIsUNCServer(pathbuf))
            drivetype = DRIVE_REMOTE;
        else
        {
            PathStripToRoot(pathbuf);
            PathAddBackslash(pathbuf);
            if (wcsncmp(pathbuf, drivetypepathcache, MAX_PATH-1)==0)       // MAX_PATH ok.
                drivetype = drivetypecache[26];
            else
            {
                CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) L"GetDriveType for %s\n", pathbuf);
                drivetype = GetDriveType(pathbuf);
                drivetypecache[26] = drivetype;
                wcsncpy_s(drivetypepathcache, pathbuf, MAX_PATH);            // MAX_PATH ok.
            }
        }
    }
    if ((drivetype == DRIVE_REMOVABLE)&&(!IsRemovable()))
        return FALSE;
    if ((drivetype == DRIVE_FIXED)&&(!IsFixed()))
        return FALSE;
    if (((drivetype == DRIVE_REMOTE)||(drivetype == DRIVE_NO_ROOT_DIR))&&(!IsRemote()))
        return FALSE;
    if ((drivetype == DRIVE_CDROM)&&(!IsCDRom()))
        return FALSE;
    if ((drivetype == DRIVE_RAMDISK)&&(!IsRAM()))
        return FALSE;
    if ((drivetype == DRIVE_UNKNOWN)&&(IsUnknown()))
        return FALSE;

    return TRUE;
}