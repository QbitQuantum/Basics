/* good1() reverses the blocks on the goto statement */
static void good1()
{
    goto sink;
sink:
    {
        HANDLE hMutex = NULL;
        hMutex = CreateMutexW(NULL, FALSE, NULL);
        /* FIX: Check the return value of CreateMutex() for NULL */
        if (hMutex == NULL)
        {
            exit(1);
        }
        /* We'll leave out most of the implementation since it has nothing to do with the CWE
         * and since the checkers are looking for certain function calls anyway */
        CloseHandle(hMutex);
    }
}