void get_gcin_dir(char *tt)
{
#if WIN32
  SHGetFolderPathA(NULL,CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, tt);
  strcat(tt,"\\gcin");
#else
    strcpy(tt,(char *)getenv("HOME"));
    strcat(tt,"/.gcin");
#endif
}