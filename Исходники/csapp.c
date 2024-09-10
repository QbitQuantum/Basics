void Fstat(int fd, struct stat *buf)
{
    if (fstat(fd, buf) < 0)
        unix_error("Fstat error");
}