static void makepath( char* path, const char* drive, const char* dir, const char* fname, const char* ext )
{
    path[2] = '\0';     //avoid bug in _makepath
    _makepath( path, drive, dir, fname, ext );
}