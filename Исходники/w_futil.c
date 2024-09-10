/**
 * Finds file separator in the path, returning -1 if separator
 * is not found
 */
int FILE_FindSeparator(Str s) 
{
    /* 
     * In Windows both the backslash ( \) and the forward slash (/) are 
     * valid path delimiters 
     */
    Str sep1 = StrChr(s, TEXT('\\'));
    Str sep2 = StrChr(s, TEXT('/'));
    size_t offset;
    if (sep1 && sep2) {
        offset = MIN(sep1-s, sep2-s);
    } else if (sep1) {
        offset = (sep1-s);
    } else if (sep2) {
        offset = (sep2-s);
    } else {
        return -1;
    }
    ASSERT(offset <= INT_MAX);
    return (int)offset;
}