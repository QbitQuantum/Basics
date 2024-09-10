/**
 * Print out a comprehensive version string which includes the interpreter
 * version, date and time built, etc. This requires starting up the interpreter
 * and ending it. May be over-kill.
 *
 * If we fail to start the interpreter, we just ignore it and print out the
 * standard version string.
 */
static void printFullVersion(void)
{
    RexxThreadContext *c;
    RexxInstance      *interpreter;

    if ( RexxCreateInterpreter(&interpreter, &c, NULL) )
    {
        char *buf = getCompleteVersion(c);
        if ( buf )
        {
            printf(buf);
            LocalFree(buf);
        }
        else
        {
            printStandardVersion();
        }

        interpreter->Terminate();
        return;
    }

    printStandardVersion();
    return;
}