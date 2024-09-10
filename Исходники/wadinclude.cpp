void            SaveWadincludeFile(const char* const filename)
{
    char*           fname;
    FILE*           file;
    int             x;
    unsigned        len = strlen(filename) + 5;

    fname = (char*)Alloc(len);
    safe_snprintf(fname, len, "%s.wic", filename);

    _unlink(fname);

    file = SafeOpenWrite(fname);

    WadInclude_i it;
    for (it = g_WadInclude.begin(); it != g_WadInclude.end(); it++)
    {
        x = it->size();
        if (x)
        {
            SafeWrite(file, it->c_str(), x);
            SafeWrite(file, ";", 1);
        }
    }

    Free(fname);
    fclose(file);
}