void CWE252_Unchecked_Return_Value__char_rename_05_bad()
{
    if(staticTrue)
    {
        /* FLAW: Do not check the return value */
        RENAME(OLD_BAD_FILE_NAME, "newbadfilename.txt");
    }
}