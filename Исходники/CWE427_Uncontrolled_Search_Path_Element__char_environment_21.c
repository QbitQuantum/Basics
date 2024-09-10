static void goodG2B1()
{
    char * data;
    char dataBuffer[250] = "PATH=";
    data = dataBuffer;
    goodG2B1Static = 0; /* false */
    data = goodG2B1Source(data);
    /* POTENTIAL FLAW: Set a new environment variable with a path that is possibly insecure */
    PUTENV(data);
}