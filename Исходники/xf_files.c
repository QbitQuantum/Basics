/* open-by-name support for file descriptors */
afs_uint32
xfon_fd(XFILE * X, int flag, char *name)
{
    int fd = atoi(name);
    return xfopen_fd(X, flag, fd);
}