void CWE252_Unchecked_Return_Value__wchar_t_fputc_11_bad()
{
    if(globalReturnsTrue())
    {
        /* FLAW: Do not check the return value */
        fputwc((wchar_t)L'A', stdout);
    }
}