void CWE78_OS_Command_Injection__wchar_t_file_w32_spawnlp_61_bad()
{
    wchar_t * data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    data = CWE78_OS_Command_Injection__wchar_t_file_w32_spawnlp_61b_badSource(data);
    /* wspawnlp - searches for the location of the command among
     * the directories specified by the PATH environment variable */
    /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
    _wspawnlp(_P_WAIT, COMMAND_INT, COMMAND_INT, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
}