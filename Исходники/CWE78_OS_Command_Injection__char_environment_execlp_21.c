void CWE78_OS_Command_Injection__char_environment_execlp_21_bad()
{
    char * data;
    char dataBuffer[100] = "";
    data = dataBuffer;
    badStatic = 1; /* true */
    data = badSource(data);
    /* execlp - searches for the location of the command among
     * the directories specified by the PATH environment variable */
    /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
    EXECLP(COMMAND_INT, COMMAND_INT, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
}