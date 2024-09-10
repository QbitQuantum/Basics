CWE36_Absolute_Path_Traversal__wchar_t_environment_ofstream_84_bad::CWE36_Absolute_Path_Traversal__wchar_t_environment_ofstream_84_bad(wchar_t * dataCopy)
{
    data = dataCopy;
    {
        /* Append input from an environment variable to data */
        size_t dataLen = wcslen(data);
        wchar_t * environment = GETENV(ENV_VARIABLE);
        /* If there is data in the environment variable */
        if (environment != NULL)
        {
            /* POTENTIAL FLAW: Read data from an environment variable */
            wcsncat(data+dataLen, environment, FILENAME_MAX-dataLen-1);
        }
    }
}