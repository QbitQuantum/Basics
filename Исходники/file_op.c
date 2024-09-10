/* Get basename of path */
char *basename_ex(char *path)
{
    return (PathFindFileNameA(path));
}