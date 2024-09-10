void CWE252_Unchecked_Return_Value__wchar_t_rename_10_bad()
{
    if(globalTrue)
    {
        /* FLAW: Do not check the return value */
        RENAME(OLD_BAD_FILE_NAME, L"newbadfilename.txt");
    }
}