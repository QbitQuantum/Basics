void CWE253_Incorrect_Check_of_Function_Return_Value__wchar_t_w32CreateMutex_15_bad()
{
    switch(6)
    {
    case 6:
    {
        HANDLE hMutex = NULL;
        hMutex = CreateMutexW(NULL, FALSE, NULL);
        /* FLAW: If CreateMutexW() failed, the return value will be NULL,
           but we are checking to see if the return value is INVALID_HANDLE_VALUE */
        if (hMutex == INVALID_HANDLE_VALUE)
        {
            exit(1);
        }
        /* We'll leave out most of the implementation since it has nothing to do with the CWE
         * and since the checkers are looking for certain function calls anyway */
        CloseHandle(hMutex);
    }
    break;
    default:
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
        break;
    }
}