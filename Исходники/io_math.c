int fseeko64(FILE *fp, off64_t offset, int whence)
{
    return _fseeki64(fp, (int64_t)offset, whence);
}