/* goodG2B uses the GoodSource with the BadSink */
void CWE78_OS_Command_Injection__char_file_execl_63b_goodG2BSink(char * * dataPtr)
{
    char * data = *dataPtr;
    /* execl - specify the path where the command is located */
    /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
    EXECL(COMMAND_INT_PATH, COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL);
}