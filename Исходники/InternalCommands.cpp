int Shell::isInternalCommand(const CString& command)
{
    CString cmd = command.toLower();
    if (cmd == "help" || cmd == "?")
    {
        return COMMAND_HELP;
    }
    else if (cmd == "ls" || cmd == "dir")
    {
        return COMMAND_LS;
    }
    else if (cmd == "cd")
    {
        return COMMAND_CD;
    }
    else if (cmd == "cat" || cmd == "type")
    {
        return COMMAND_CAT;
    }
    else if (cmd == "uname" || cmd == "ver")
    {
        return COMMAND_UNAME;
    }
    else if (cmd == "echo")
    {
        return COMMAND_ECHO;
    }
    else if (cmd == "clear" || cmd == "cls")
    {
        return COMMAND_CLEAR;
    }
    else if (cmd == "ps")
    {
        return COMMAND_PS;
    }
    else if (cmd == "mem")
    {
        return COMMAND_MEM;
    }
    else if (cmd == "kill")
    {
        return COMMAND_KILL;
    }
    else if (cmd == "exec")
    {
        return COMMAND_EXEC;
    }
    else if (cmd == "shutdown")
    {
        return COMMAND_SHUTDOWN;
    }
    else if (cmd == "halt")
    {
        return COMMAND_HALT;
    }
    else if (cmd == "reboot")
    {
        return COMMAND_REBOOT;
    }

    return COMMAND_NONE;
}