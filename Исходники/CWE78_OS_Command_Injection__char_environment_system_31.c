void CWE78_OS_Command_Injection__char_environment_system_31_bad()
{
    char * data;
    char data_buf[100] = FULL_COMMAND;
    data = data_buf;
    {
        /* Append input from an environment variable to data */
        size_t dataLen = strlen(data);
        char * environment = GETENV(ENV_VARIABLE);
        /* If there is data in the environment variable */
        if (environment != NULL)
        {
            /* POTENTIAL FLAW: Read data from an environment variable */
            strncat(data+dataLen, environment, 100-dataLen-1);
        }
    }
    {
        char * dataCopy = data;
        char * data = dataCopy;
        /* POTENTIAL FLAW: Execute command in data possibly leading to command injection */
        if (SYSTEM(data) <= 0)
        {
            printLine("command execution failed!");
            exit(1);
        }
    }
}