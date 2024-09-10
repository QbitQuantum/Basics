static void goodB2G2()
{
    char * data;
    data = (char *)malloc(100*sizeof(char));
    data[0] = '\0';
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
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_environment_22_goodB2G2Global = 1; /* true */
    CWE761_Free_Pointer_Not_at_Start_of_Buffer__char_environment_22_goodB2G2Sink(data);
}