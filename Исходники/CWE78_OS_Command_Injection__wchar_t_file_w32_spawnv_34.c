void CWE78_OS_Command_Injection__wchar_t_file_w32_spawnv_34_bad()
{
    wchar_t * data;
    CWE78_OS_Command_Injection__wchar_t_file_w32_spawnv_34_unionType myUnion;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    {
        /* Read input from a file */
        size_t dataLen = wcslen(data);
        FILE * pFile;
        /* if there is room in data, attempt to read the input from a file */
        if (100-dataLen > 1)
        {
            pFile = fopen(FILENAME, "r");
            if (pFile != NULL)
            {
                /* POTENTIAL FLAW: Read data from a file */
                if (fgetws(data+dataLen, (int)(100-dataLen), pFile) == NULL)
                {
                    printLine("fgetws() failed");
                    /* Restore NUL terminator if fgetws fails */
                    data[dataLen] = L'\0';
                }
                fclose(pFile);
            }
        }
    }
    myUnion.unionFirst = data;
    {
        wchar_t * data = myUnion.unionSecond;
        {
            wchar_t *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
            /* wspawnv - specify the path where the command is located */
            /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
            _wspawnv(_P_WAIT, COMMAND_INT_PATH, args);
        }
    }
}