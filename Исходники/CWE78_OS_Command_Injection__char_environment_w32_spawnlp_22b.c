char * CWE78_OS_Command_Injection__char_environment_w32_spawnlp_22_badSource(char * data)
{
    if(CWE78_OS_Command_Injection__char_environment_w32_spawnlp_22_badGlobal)
    {
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
    return data;
}