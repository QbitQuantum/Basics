void CWE252_Unchecked_Return_Value__wchar_t_fputs_18_bad()
{
    goto sink;
sink:
    /* FLAW: Do not check the return value */
    fputws(L"string", stdout);
}