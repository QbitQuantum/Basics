void CWE78_OS_Command_Injection__char_console_w32_execv_01_bad()
{
    char * data;
    char dataBuffer[100] = "";
    data = dataBuffer;
    {
        /* Read input from the console */
        size_t dataLen = strlen(data);
        /* if there is room in data, read into it from the console */
        if (100-dataLen > 1)
        {
            /* POTENTIAL FLAW: Read data from the console */
            if (fgets(data+dataLen, (int)(100-dataLen), stdin) != NULL)
            {
                /* The next few lines remove the carriage return from the string that is
                 * inserted by fgets() */
                dataLen = strlen(data);
                if (dataLen > 0 && data[dataLen-1] == '\n')
                {
                    data[dataLen-1] = '\0';
                }
            }
            else
            {
                printLine("fgets() failed");
                /* Restore NUL terminator if fgets fails */
                data[dataLen] = '\0';
            }
        }
    }
    {
        char *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
        /* execv - specify the path where the command is located */
        /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
        EXECV(COMMAND_INT_PATH, args);
    }
}