void CWE78_OS_Command_Injection__wchar_t_environment_popen_65_bad()
{
    wchar_t * data;
    /* define a function pointer */
    void (*funcPtr) (wchar_t *) = CWE78_OS_Command_Injection__wchar_t_environment_popen_65b_badSink;
    wchar_t data_buf[100] = FULL_COMMAND;
    data = data_buf;
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
    /* use the function pointer */
    funcPtr(data);
}