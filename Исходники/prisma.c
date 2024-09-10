char* _prisma_trytogettermname() {
    static char _prisma_termname[_PRISMA_TERMNAME_LENGTH];

#ifdef _PRISMA_LINUX 
    char *tmp = getnameof(getppidof(getsid(getpid())));
    if(tmp) {
        strncpy(_prisma_termname, tmp, _PRISMA_TERMNAME_LENGTH);
        if(!strncmp(_prisma_termname, "initdline", _PRISMA_TERMNAME_LENGTH)
        || !strncmp(_prisma_termname, "konsole", _PRISMA_TERMNAME_LENGTH))
            return _prisma_termname;
    } 

#ifdef _GNU_SOURCE
    strncpy(_prisma_termname, secure_getenv("TERM"), _PRISMA_TERMNAME_LENGTH);
#else
    strncpy(_prisma_termname, getenv("TERM"), _PRISMA_TERMNAME_LENGTH);
#endif

#elif defined _PRISMA_WINDOWS
    if(GetConsoleOriginalTitleA(&_prisma_termname[9], 
                _PRISMA_TERMNAME_LENGTH-9)) {
        strncpy(_prisma_termname, "windows, ", 9);
    } else
        strncpy(_prisma_termname, "windows, unknown", _PRISMA_TERMNAME_LENGTH);
#else
    strncpy(_prisma_termname, "unknown", _PRISMA_TERMNAME_LENGTH);
#endif

    return _prisma_termname;
}