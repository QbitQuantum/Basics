static void goodG2B2()
{
    wchar_t * data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    CWE78_OS_Command_Injection__wchar_t_console_w32spawnl_22_goodG2B2Global = 1; /* true */
    data = CWE78_OS_Command_Injection__wchar_t_console_w32spawnl_22_goodG2B2Source(data);
    /* wspawnl - specify the path where the command is located */
    /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
    _wspawnl(_P_WAIT, COMMAND_INT_PATH, COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
}