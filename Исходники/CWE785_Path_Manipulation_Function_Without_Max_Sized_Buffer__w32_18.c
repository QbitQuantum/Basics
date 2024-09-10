/* good1() reverses the blocks on the goto statement */
static void good1()
{
    goto sink;
sink:
    {
        /* FIX: ensure MAX_PATH allocated in 'path' */
        char path[MAX_PATH];
        DWORD length;
        length = GetCurrentDirectoryA(MAX_PATH, path);
        if (length == 0 || length >= MAX_PATH)
        {
            exit(1); /* failure conditions for this API call */
        }
        if (!PathAppendA(path, "AAAAAAAAAAAA"))
        {
            exit(1);
        }
        printLine(path);
    }
}