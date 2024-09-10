char * ChangeToDir (const char *Dirname)
{
    STRUCT_STAT st;

    if (STAT(Dirname, &st))
    {
        // doen't exist; must create it
        MKDIR (Dirname);
    }
    if (S_ISDIR(st.st_mode) == 0) 
    {
        // it's not a dir, must create a dir
        MKDIR (Dirname);
    }
    char *oldDirname = GetCurrDir ();
    CHDIR(Dirname);
    return oldDirname;
}