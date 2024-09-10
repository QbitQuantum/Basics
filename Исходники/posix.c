void uninitvar(int fd)
{
    int x;
    char buf[2];
    int decimal, sign;
    double d;
    void *p;
    // cppcheck-suppress uninitvar
    write(x,"ab",2);
    // cppcheck-suppress uninitvar
    write(fd,buf,2); // #6325
    // cppcheck-suppress uninitvar
    write(fd,"ab",x);
    // cppcheck-suppress uninitvar
    write(fd,p,2);


    /* int regcomp(regex_t *restrict preg, const char *restrict pattern, int cflags); */
    regex_t reg;
    const char * pattern;
    int cflags;
    // cppcheck-suppress uninitvar
    regcomp(&reg, pattern, cflags);
    pattern="";
    // cppcheck-suppress uninitvar
    regcomp(&reg, pattern, cflags);
    regerror(0, &reg, 0, 0);
    // cppcheck-suppress uninitvar
    // cppcheck-suppress unreadVariable
    // cppcheck-suppress ecvtCalled
    char *buffer = ecvt(d, 11, &decimal, &sign);
    // cppcheck-suppress gcvtCalled
    gcvt(3.141, 2, buf);

    char *filename;
    struct utimbuf *times;
    // cppcheck-suppress uninitvar
    // cppcheck-suppress utimeCalled
    utime(filename, times);
    struct timeval times1[2];
    // cppcheck-suppress uninitvar
    // cppcheck-suppress utimeCalled
    utime(filename, times1);
}