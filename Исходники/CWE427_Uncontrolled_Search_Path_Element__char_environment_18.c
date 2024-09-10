void CWE427_Uncontrolled_Search_Path_Element__char_environment_18_bad()
{
    char * data;
    char dataBuffer[250] = "PATH=";
    data = dataBuffer;
    goto source;
source:
    {
        /* Append input from an environment variable to data */
        size_t dataLen = strlen(data);
        char * environment = GETENV(ENV_VARIABLE);
        /* If there is data in the environment variable */
        if (environment != NULL)
        {
            /* POTENTIAL FLAW: Read data from an environment variable */
            strncat(data+dataLen, environment, 250-dataLen-1);
        }
    }
    /* POTENTIAL FLAW: Set a new environment variable with a path that is possibly insecure */
    PUTENV(data);
}