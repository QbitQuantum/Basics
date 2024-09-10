void CWE252_Unchecked_Return_Value__char_puts_12_bad()
{
    if(globalReturnsTrueOrFalse())
    {
        /* FLAW: Do not check the return value */
        PUTS("string");
    }
    else
    {
        /* FIX: check the return value */
        if (PUTS("string") == EOF)
        {
            printLine("puts failed!");
        }
    }
}