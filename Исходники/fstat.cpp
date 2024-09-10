static bool GetStatByHandle(TSystemFStat& fs, FHANDLE f) {
#ifdef _win_
    return GetFileInformationByHandle(f, &fs);
#else
    return !fstat(f, &fs);
#endif
}