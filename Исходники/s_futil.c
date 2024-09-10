/**
 * Returns pointer to buffer containing directory part of the given path.
 * The returned string is either empty or ends with file separator character. 
 * Under Win32, if may also look like "C:", but in either case file name 
 * can be simply appended to it. The return buffer has 'extra' additional 
 * characters allocated past the end of the string. The function only 
 * returns NULL if input parameter is NULL or memory allocation fails. 
 */
Char * FILE_DirName(Str path, int extra) 
{
    Char * dir = NULL;
    ASSERT(path);
    ASSERT(extra >= 0);
    if (path) {
        size_t len = FILE_FilePart(path) - path;
        size_t size = len + 1;
        if (extra >= 0) size += extra;
        dir = MEM_NewArray(Char,size);

        /* copy portion of the source path */
        if (dir) {
            if (len > 0) StrnCpy(dir, path, len);
            dir[len] = 0;
        }
    }
    return dir;
}