CWE134_Uncontrolled_Format_String__char_environment_vfprintf_84_goodB2G::CWE134_Uncontrolled_Format_String__char_environment_vfprintf_84_goodB2G(char * dataCopy)
{
    data = dataCopy;
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
}