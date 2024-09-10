static long fdTell(FD_t fd)
{
    return lseek(Fileno(fd), 0, SEEK_CUR);
}