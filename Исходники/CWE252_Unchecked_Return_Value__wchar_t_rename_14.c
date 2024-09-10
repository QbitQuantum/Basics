/* good2() reverses the bodies in the if statement */
static void good2()
{
    if(globalFive==5)
    {
        /* FIX: check the return value */
        if (RENAME(OLD_GOOD_FILE_NAME, L"newgoodfilename.txt") != 0)
        {
            printLine("rename failed!");
        }
    }
}