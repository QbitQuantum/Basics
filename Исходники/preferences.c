void
prefs_close (void *node)
{
    HKEY hk;

    hk=(HKEY) node;

    RegFlushKey(hk);
    RegCloseKey(hk);
}