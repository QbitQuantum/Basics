void GetExecutableDir(wchar_t* outdir, int outdir_length)
{
    // Without slash at end.

    // This path is longer than MAX_PATH, do not use it with
    // windows api functions as you might get buffer overflows.

    wchar_t longpath[1024];
    GetExecutablePath(longpath, _countof(longpath));

    wchar_t drive[3];
    wchar_t dir[768];
    wchar_t fname[256];
    wchar_t ext[32];

    errno_t result = _wsplitpath_s(longpath, drive, _countof(drive), dir, _countof(dir), fname, _countof(fname), ext, _countof(ext));
    ASSERT_EXIT((result == 0), "_wsplitpath_s(longpath)");

    swprintf_s(outdir, outdir_length, L"%s%s", drive, dir);

    // remove slash at end
    int len = wcslen(outdir);
    if (outdir[len-1] == '\\' || outdir[len-1] == '/') {
        outdir[len-1] = 0;
    }
}