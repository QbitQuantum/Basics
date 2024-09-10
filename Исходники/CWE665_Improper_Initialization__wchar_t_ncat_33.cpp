void bad()
{
    wchar_t * data;
    wchar_t * &dataRef = data;
    wchar_t dataBuffer[100];
    data = dataBuffer;
    /* FLAW: Do not initialize data */
    ; /* empty statement needed for some flow variants */
    {
        wchar_t * data = dataRef;
        {
            size_t sourceLen;
            wchar_t source[100];
            wmemset(source, L'C', 100-1); /* fill with L'C's */
            source[100-1] = L'\0'; /* null terminate */
            sourceLen = wcslen(source);
            /* POTENTIAL FLAW: If data is not initialized properly, wcsncat() may not function correctly */
            wcsncat(data, source, sourceLen);
            printWLine(data);
        }
    }
}