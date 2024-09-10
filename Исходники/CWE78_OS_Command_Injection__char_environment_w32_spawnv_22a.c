static void goodG2B2()
{
    char * data;
    char dataBuffer[100] = "";
    data = dataBuffer;
    CWE78_OS_Command_Injection__char_environment_w32_spawnv_22_goodG2B2Global = 1; /* true */
    data = CWE78_OS_Command_Injection__char_environment_w32_spawnv_22_goodG2B2Source(data);
    {
        char *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
        /* spawnv - specify the path where the command is located */
        /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
        _spawnv(_P_WAIT, COMMAND_INT_PATH, args);
    }
}