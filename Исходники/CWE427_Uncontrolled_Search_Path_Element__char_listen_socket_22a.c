void CWE427_Uncontrolled_Search_Path_Element__char_listen_socket_22_bad()
{
    char * data;
    char dataBuffer[250] = "PATH=";
    data = dataBuffer;
    CWE427_Uncontrolled_Search_Path_Element__char_listen_socket_22_badGlobal = 1; /* true */
    data = CWE427_Uncontrolled_Search_Path_Element__char_listen_socket_22_badSource(data);
    /* POTENTIAL FLAW: Set a new environment variable with a path that is possibly insecure */
    PUTENV(data);
}