void lock(void)
{
    FILE *f;
    struct flock flo;

    f = lockfile();

    flo.l_start  = flo.l_len = 0;
    flo.l_whence = SEEK_SET;
    flo.l_type   = F_WRLCK;

    if (fcntl(fileno(f), F_SETLKW, &flo) == -1) {
        perror("bee-dep: lock");
        exit(EXIT_FAILURE);
    }
}