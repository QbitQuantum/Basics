uint64 XlMakeFileTime(struct tm* local)
{
    return _mktime64(local);
}