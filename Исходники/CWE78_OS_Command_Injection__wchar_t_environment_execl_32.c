void CWE78_OS_Command_Injection__wchar_t_environment_execl_32_bad()
{
    wchar_t * data;
    wchar_t * *dataPtr1 = &data;
    wchar_t * *dataPtr2 = &data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    {
        wchar_t * data = *dataPtr1;
        {
            /* Append input from an environment variable to data */
            size_t dataLen = wcslen(data);
            wchar_t * environment = GETENV(ENV_VARIABLE);
            /* If there is data in the environment variable */
            if (environment != NULL)
            {
                /* POTENTIAL FLAW: Read data from an environment variable */
                wcsncat(data+dataLen, environment, 100-dataLen-1);
            }
        }
        *dataPtr1 = data;
    }
    {
        wchar_t * data = *dataPtr2;
        /* wexecl - specify the path where the command is located */
        /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
        EXECL(COMMAND_INT_PATH, COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
    }
}