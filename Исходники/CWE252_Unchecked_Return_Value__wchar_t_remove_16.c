void CWE252_Unchecked_Return_Value__wchar_t_remove_16_bad()
{
    while(1)
    {
        /* FLAW: Do not check the return value */
        REMOVE(L"removemebad.txt");
        break;
    }
}