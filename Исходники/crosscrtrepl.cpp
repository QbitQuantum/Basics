char* __strerror(int errnum) {
#ifdef _MSC_VER
    char errBuf[512];
    strerror_s(errBuf, errnum);
    return errBuf;
#else
    return strerror(errnum);
#endif
};