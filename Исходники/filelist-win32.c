int compareTime(const char* file1, const char* file2) {
#ifdef _WIN32_WCE
    WCHAR tfn1[MAX_PATH];
    WCHAR tfn2[MAX_PATH];
    convertAsciiToUnicode(tfn1, MAX_PATH, file1);
    convertAsciiToUnicode(tfn2, MAX_PATH, file2);
#else
    const char* tfn1 = file1;
    const char* tfn2 = file2;
#endif
    FILETIME ft1, ft2;
    int hDiff, lDiff;

    getFileTime(tfn1, &ft1);
    getFileTime(tfn2, &ft2);

    hDiff = ft1.dwHighDateTime - ft2.dwHighDateTime;
    lDiff = ft1.dwLowDateTime - ft2.dwLowDateTime;
    if (hDiff) {
        return hDiff;
    } else {
        return lDiff;
    }
}