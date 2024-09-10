/**
 * Process a signal based on current command handler settings.
 *
 * @param dwCtrlType The type of exception.
 *
 * @return true if we handled the signal, false if it should be
 *         passed up the handler chain.
 */
bool SystemInterpreter::processSignal(DWORD dwCtrlType)
{
    /* Ignore Ctrl+C if console is running in console */
    if (exceptionConsole)
    {
        GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, exceptionHostProcessId);
        return true;   /* ignore signal */
    }

    if (exceptionHostProcess)
    {
        GenerateConsoleCtrlEvent(CTRL_C_EVENT, exceptionHostProcessId);
        TerminateProcess(exceptionHostProcess, -1);
    }
    // if this is a ctrl_C, try to halt all of the activities.  If we hit this
    // in a situation where we still have one pending, then we'll allow the system
    // to kill the process.
    if (dwCtrlType == CTRL_C_EVENT)
    {
        return Interpreter::haltAllActivities(OREF_NULL);
    }
    return true;      /* ignore signal */
}