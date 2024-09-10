static void good1()
{
    /* FIX: check the return value */
    if (RENAME(OLD_GOOD_FILE_NAME, "newgoodfilename.txt") != 0)
    {
        printLine("rename failed!");
    }
}