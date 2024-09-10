CWE78_OS_Command_Injection__char_environment_system_83_goodG2B::~CWE78_OS_Command_Injection__char_environment_system_83_goodG2B()
{
    /* POTENTIAL FLAW: Execute command in data possibly leading to command injection */
    if (SYSTEM(data) <= 0)
    {
        printLine("command execution failed!");
        exit(1);
    }
}