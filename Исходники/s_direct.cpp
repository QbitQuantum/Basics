int FileFind::FindFirst(FileInfo **fi) {
#if defined(USE_DIRENT)
    if (dir)
        closedir(dir);
    if ((dir = opendir(Directory)) == 0)
        return -1;
    return FindNext(fi);
#elif defined(OS2) && !defined(USE_DIRENT)
    char fullpattern[MAXPATH];
    HDIR hdir = HDIR_CREATE;
    ULONG attr = FILE_ARCHIVED | FILE_READONLY;
    ULONG count = 1;
    FILEFINDBUF3 find; // need to improve to fetch multiple entries at once
    char fullpath[MAXPATH];
    char *name;
    struct tm t;
    int rc;

    if (dir)
        DosFindClose(dir);

    if (Flags & ffDIRECTORY)
        attr |= FILE_DIRECTORY;

    if (Flags & ffHIDDEN)
        attr |= FILE_HIDDEN | FILE_SYSTEM; // separate ?

    if (Pattern)
        JoinDirFile(fullpattern, Directory, Pattern);
    else
        JoinDirFile(fullpattern, Directory, "*");

    if ((rc = DosFindFirst(fullpattern,
                           &hdir,
                           attr,
                           &find, sizeof(find),
                           &count,
                           FIL_STANDARD)) != 0) {
        //fprintf(stderr, "%s: %d\n\n", fullpattern, rc);
        return -1;
    }
    dir = hdir;
    if (count != 1)
        return -1;
    name = find.achName;
    if (Flags & ffFULLPATH) {
        JoinDirFile(fullpath, Directory, name);
        name = fullpath;
    }
    memset((void *)&t, 0, sizeof(t));
    t.tm_year = find.fdateLastWrite.year + 80; // ugh!
    t.tm_mon = find.fdateLastWrite.month - 1;
    t.tm_mday = find.fdateLastWrite.day;
    t.tm_hour = find.ftimeLastWrite.hours;
    t.tm_min = find.ftimeLastWrite.minutes;
    t.tm_sec = find.ftimeLastWrite.twosecs * 2; // ugh!
    t.tm_isdst = -1;
    *fi = new FileInfo(name,
                       (find.attrFile & FILE_DIRECTORY) ? fiDIRECTORY : fiFILE,
                       find.cbFile,
                       mktime(&t));
    return 0;
#elif defined(NT) && !defined(USE_DIRENT)
#if defined(USE_VCFIND)
    char fullpattern[MAXPATH];

    _finddata_t find; // need to improve to fetch multiple entries at once
    char fullpath[MAXPATH];
    char *name;
    struct tm t;
    int rc;

    if (dir)
        _findclose(dir);

    /*if (Flags & ffDIRECTORY)
    attr |= FILE_DIRECTORY;

    if (Flags & ffHIDDEN)
    attr |= FILE_HIDDEN | FILE_SYSTEM; // separate ?
    */
    if (Pattern)
        JoinDirFile(fullpattern, Directory, Pattern);
    else
        JoinDirFile(fullpattern, Directory, "*");

    if ((rc = _findfirst(fullpattern, &find)) == -1) {
        //        fprintf(stderr, "%s: %d\n\n", fullpattern, rc);
        return -1;
    }
    dir = rc;

    name = find.name;
    if (Flags & ffFULLPATH) {
        JoinDirFile(fullpath, Directory, name);
        name = fullpath;
    }

    *fi = new FileInfo(name,
                       (find.attrib & _A_SUBDIR) ? fiDIRECTORY : fiFILE,
                       find.size,
                       find.time_create);
    return 0;
#else
    char fullpattern[MAXPATH];

    WIN32_FIND_DATA find; // need to improve to fetch multiple entries at once
    char fullpath[MAXPATH];
    char *name;
    struct tm t;
    SYSTEMTIME st;
    FILETIME localft;                   // needed for time conversion
    int rc;

    if (dir)
        _findclose(dir);

    /*if (Flags & ffDIRECTORY)
    attr |= FILE_DIRECTORY;

    if (Flags & ffHIDDEN)
    attr |= FILE_HIDDEN | FILE_SYSTEM; // separate ?
    */
    if (Pattern)
        JoinDirFile(fullpattern, Directory, Pattern);
    else
        JoinDirFile(fullpattern, Directory, "*");

    if ((rc = (int) FindFirstFile(fullpattern, &find)) < 0) {
        //fprintf(stderr, "%s: %d\n\n", fullpattern, rc);
        return -1;
    }
    dir = rc;

    name = find.cFileName;
    if (Flags & ffFULLPATH) {
        JoinDirFile(fullpath, Directory, name);
        name = fullpath;
    }

    /*
    * since filetime is in UTC format we need to convert it first to
    * localtime and when we have "correct" time we can use it.
    */

    FileTimeToLocalFileTime(&find.ftLastWriteTime, &localft);
    FileTimeToSystemTime(&localft, &st);

    t.tm_year = st.wYear - 1900;
    t.tm_mon = st.wMonth - 1;           // in system time january is 1...
    t.tm_mday = st.wDay;
    t.tm_hour = st.wHour;
    t.tm_min = st.wMinute;
    t.tm_sec = st.wSecond;
    t.tm_isdst = -1;


    *fi = new FileInfo(name,
                       (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? fiDIRECTORY : fiFILE,
                       find.nFileSizeLow, // !!!
                       mktime(&t));
    return 0;
#endif
#endif
}