void kpr2jsResolvePath(xsMachine* the)
{
#if mxWindows
    char* srcPath;
    char aPath[1024];
    DWORD attributes;
    int aResult = 0;

    srcPath = xsToString(xsArg(0));
    if (_fullpath(aPath, srcPath, 1024) != NULL) {
        attributes = GetFileAttributes(aPath);
        if (attributes != 0xFFFFFFFF) {
            if (xsToInteger(xsArgc) == 1)
                aResult = 1;
            else if (xsToBoolean(xsArg(1)))
                aResult = (attributes & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
            else
                aResult = (attributes & FILE_ATTRIBUTE_DIRECTORY) ? 0 : 1;
        }
    }
#else
    char* srcPath;
    char aPath[PATH_MAX];
    struct stat a_stat;
    int aResult = 0;

    srcPath = xsToString(xsArg(0));
    if (realpath(srcPath, aPath) != NULL) {
        if (stat(aPath, &a_stat) == 0) {
            if (xsToInteger(xsArgc) == 1)
                aResult = 1;
            else if (xsToBoolean(xsArg(1)))
                aResult = S_ISDIR(a_stat.st_mode) ? 1 : 0;
            else
                aResult = S_ISREG(a_stat.st_mode) ? 1 : 0;
        }
    }
#endif
    if (aResult) {
        if (xsToBoolean(xsArg(1))) {
            aResult = strlen(aPath) - 1;
            if (aPath[aResult] == mxSeparator)
                aPath[aResult] = 0;
        }
        xsResult = xsString(aPath);
    }
}