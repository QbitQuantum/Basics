/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2BSource(wchar_t * &password)
{
    password = (wchar_t *)malloc(100*sizeof(wchar_t));
    if (password == NULL)
    {
        printLine("Memory could not be allocated");
        exit(1);
    }
    /* FIX: Use VirtualLock() to lock the buffer into memory */
    if(!VirtualLock(password, 100*sizeof(wchar_t)))
    {
        printLine("Memory could not be locked");
        exit(1);
    }
    /* INCIDENTAL FLAW: CWE-259 Hardcoded Password */
    wcscpy(password, L"Password1234!");
}