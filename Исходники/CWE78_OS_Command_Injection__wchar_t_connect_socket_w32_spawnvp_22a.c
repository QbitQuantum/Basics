static void goodG2B2()
{
    wchar_t * data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    CWE78_OS_Command_Injection__wchar_t_connect_socket_w32_spawnvp_22_goodG2B2Global = 1; /* true */
    data = CWE78_OS_Command_Injection__wchar_t_connect_socket_w32_spawnvp_22_goodG2B2Source(data);
    {
        wchar_t *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
        /* wspawnvp - searches for the location of the command among
         * the directories specified by the PATH environment variable */
        /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
        _wspawnvp(_P_WAIT, COMMAND_INT, args);
    }
}