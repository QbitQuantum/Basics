static void goodG2B2()
{
    char * data;
    char dataBuffer[250] = "PATH=";
    data = dataBuffer;
    CWE427_Uncontrolled_Search_Path_Element__char_console_22_goodG2B2Global = 1; /* true */
    data = CWE427_Uncontrolled_Search_Path_Element__char_console_22_goodG2B2Source(data);
    /* POTENTIAL FLAW: Set a new environment variable with a path that is possibly insecure */
    PUTENV(data);
}