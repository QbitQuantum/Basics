int getTempPath(char *buff)
{
    int i;
    char *ret;
    char prefix[16];

    GetTempPath(MAX_PATH, buff);
    sprintf(prefix, "_MEI%d", getpid());

    // Windows does not have a race-free function to create a temporary
    // directory. Thus, we rely on _tempnam, and simply try several times
    // to avoid stupid race conditions.
    for (i=0;i<5;i++) {
        ret = _tempnam(buff, prefix);
        if (mkdir(ret) == 0) {
            strcpy(buff, ret);
            strcat(buff, "\\");
            free(ret);
            return 1;
        }
        free(ret);
    }
    return 0;
}