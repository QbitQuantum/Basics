int _RTL_FUNC system(const char *string)
{
    FILE *f;
    char buf[1024],*a;
    a = getenv("COMSPEC");
    if (!a)
        a = searchpath("cmd.exe");
    if (!string) {
        if (!a)
            return 0;
        else
            if (f = fopen(a,"r")) {
                fclose(f);
                return 1;
            }
            else
                return 0;
    }
    if (!a) {
        errno = ENOENT;
        return -1;
    }
    buf[0] = ' ';
    buf[1] = '/';
    buf[2] = 'C';
    buf[3] = ' ';
    strcpy(buf+4,string);
    return spawnlp(P_WAIT,a,a,buf,0);
}