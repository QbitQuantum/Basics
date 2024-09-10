void CWE377_Insecure_Temporary_File__char_tempnam_01_bad()
{
    {
        char * filename;
        int fileDesc;
        filename = TEMPNAM(NULL, NULL);
        if (filename == NULL)
        {
            exit(1);
        }
        printLine(filename);
        /* FLAW: Open a temporary file using open() and flags that do not prevent a race condition */
        fileDesc = OPEN(filename, O_RDWR|O_CREAT, S_IREAD|S_IWRITE);
        if (fileDesc != -1)
        {
            printLine("Temporary file was opened...now closing file");
            CLOSE(fileDesc);
        }
        free(filename);
    }
}