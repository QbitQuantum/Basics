static void gen_bin(char *name, char *full_src, char *minus)
{
    // doesn't have to use full path because chdir(gcin user dir)
    minus[0]=0;
    char src[128];
    strcat(strcpy(src, name),".src");

    dbg("gen_bin %s %s\n", name, src);

    if (get_gcin_user_fname(src, full_src)) {
        dbg("%s %s\n", name, full_src);
#if UNIX
        putenv("GCIN_NO_RELOAD=");
        unix_exec(GCIN_BIN_DIR"/tsa2d32 %s %s", src, name);
#else
        _putenv("GCIN_NO_RELOAD=Y");
        win32exec_va("tsa2d32", src, name, NULL);
#endif
        sprintf(minus, " -minus %s", name);
    } else
        dbg("not exist %s\n", full_src);
}