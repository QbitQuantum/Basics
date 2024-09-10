// Returns a string in /vsimem/ + prefix + count that doesn't exist when this function gets called
// It is not completely safe, open the result as soon as possible
CPLString uniq_memfname(const char *prefix)
{

// Define MRF_LOCAL_TMP to use local files instead of RAM
// #define MRF_LOCAL_TMP
#if defined(MRF_LOCAL_TMP)
    return CPLGenerateTempFilename(prefix);
#else
    CPLString fname;
    VSIStatBufL statb;
    static unsigned int cnt=0;
    do fname.Printf("/vsimem/%s_%08x",prefix, cnt++);
    while (!VSIStatL(fname, &statb));
    return fname;
#endif
}