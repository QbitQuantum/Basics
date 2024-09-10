void
    DumpFileToLog(
    char* path
    )
{
    FILE* fp;
    char buf[BUFFER_SIZE];
    char* p;

    fp = fopen_unsafe(path, "r");
    if (fp == NULL) {
        LogError("ERROR: DumpFileToLog couldn't open file '%s' with error '%s'", path, strerror_unsafe(errno));
    }
    else {
        int fd = _fileno(fp);
        struct _stat64 fileStats;
        if (fd != -1 && _fstat64(fd, &fileStats) != -1)
        {
            char creationTime[256];
            char accessTime[256];
            char currTime[256];
            __time64_t now = _time64(NULL);
            _ctime64_s(currTime, &now);
            _ctime64_s(creationTime, &fileStats.st_ctime);
            _ctime64_s(accessTime, &fileStats.st_atime);
            auto stripNewline = [](char *buf) {
                if (char *ptr = strchr(buf, '\n'))
                    *ptr = '\0';
            };
            stripNewline(creationTime);
            stripNewline(accessTime);
            stripNewline(currTime);

            LogOut("ERROR: name of output file: %s; size: %I64d; creation: %s, last access: %s, now: %s", path, fileStats.st_size, creationTime, accessTime, currTime);
        }
        if (!FNoProgramOutput)
        {
            bool printlines = !FOnlyAssertOutput;
            if (printlines)
            {
                LogOut("ERROR: bad output file follows ============");
            }
            while (fgets(buf, BUFFER_SIZE, fp) != NULL) {
                // Strip the newline, since LogOut adds one
                p = strchr(buf, '\n');
                if (p != NULL) {
                    *p = '\0';
                }
                if (!printlines && strlen(buf) > 8 && buf[0] == 'A' && buf[1] == 'S' && buf[2] == 'S' && buf[3] == 'E' && buf[4] == 'R' && buf[5] == 'T')
                {
                    printlines = true;
                    LogOut("ERROR: bad output file follows ============");
                }
                if (printlines)
                {
                    LogOut("%s", buf);
                }
            }
            if (printlines)
            {
                LogOut("ERROR: end of bad output file  ============");
            }
        }
        fclose(fp);
    }
}