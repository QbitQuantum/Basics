void CWE390_Error_Without_Action__fgets_wchar_t_18_bad()
{
    goto sink;
sink:
    {
        /* By initializing dataBuffer, we ensure this will not be the
         * CWE 690 (Unchecked Return Value To NULL Pointer) flaw for fgetws() */
        wchar_t dataBuffer[100] = L"";
        wchar_t * data = dataBuffer;
        printWLine(L"Please enter a string: ");
        /* FLAW: check the return value, but do nothing if there is an error */
        if (fgetws(data, 100, stdin) == NULL)
        {
            /* do nothing */
        }
        printWLine(data);
    }
}