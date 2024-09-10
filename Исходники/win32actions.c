static void action_copy(const char *filename)
{
    char *nuname;
    if (!getdest(filename, &nuname)) return;
    if (CopyFileA(filename, nuname, FALSE))
        logg("~%s: copied to '%s'\n", PATH_PLAIN(filename), PATH_PLAIN(nuname));
    else
    {
        logg("!Cannot copy file %s (%lu)\n", PATH_PLAIN(filename), GetLastError());
        notmoved++;
    }
    free(nuname);
}