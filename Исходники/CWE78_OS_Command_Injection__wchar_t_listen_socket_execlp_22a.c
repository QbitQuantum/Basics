static void goodG2B2()
{
    wchar_t * data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    CWE78_OS_Command_Injection__wchar_t_listen_socket_execlp_22_goodG2B2Global = 1; /* true */
    data = CWE78_OS_Command_Injection__wchar_t_listen_socket_execlp_22_goodG2B2Source(data);
    /* wexeclp - searches for the location of the command among
     * the directories specified by the PATH environment variable */
    /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
    EXECLP(COMMAND_INT, COMMAND_INT, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
}