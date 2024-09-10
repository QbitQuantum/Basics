void bad()
{
    wchar_t * data;
    wchar_t * &dataRef = data;
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
    {
        wchar_t * data = dataRef;
        {
            wchar_t *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
            /* wspawnvp - searches for the location of the command among
             * the directories specified by the PATH environment variable */
            /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
            _wspawnvp(_P_WAIT, COMMAND_INT, args);
        }
    }
}