void getOmegaRCPath()
{
#ifndef WIN32
    sprintf(Str1, "%s/.omegarc", getenv("HOME"));
#else
    SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, Str1);
    strcat(Str1, "\\.omegarc");
#endif
}