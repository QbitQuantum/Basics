/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2BSink()
{
    char * data = CWE78_OS_Command_Injection__char_console_w32_execvp_45_goodG2BData;
    {
        char *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
        /* execvp - searches for the location of the command among
         * the directories specified by the PATH environment variable */
        /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
        EXECVP(COMMAND_INT, args);
    }
}