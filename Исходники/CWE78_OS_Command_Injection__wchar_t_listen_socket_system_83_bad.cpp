CWE78_OS_Command_Injection__wchar_t_listen_socket_system_83_bad::~CWE78_OS_Command_Injection__wchar_t_listen_socket_system_83_bad()
{
    /* POTENTIAL FLAW: Execute command in data possibly leading to command injection */
    if (SYSTEM(data) <= 0)
    {
        printLine("command execution failed!");
        exit(1);
    }
}