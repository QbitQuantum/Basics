void getDebuggerInput(char * msg)
{
char command[MAX_LINE];
char * context;
jmp_buf errorJumpSave;
UINT * resultStackIdxSave;
SYMBOL * contextSave;

while(TRUE)
    {

    if(currentContext != mainContext)
        context = currentContext->name;
    else context = "";


    if(!evalSilent)
        varPrintf(OUT_CONSOLE, "\n[%s %d %s]%s", msg, recursionCount, context, footerStr);
    else evalSilent = FALSE;

    if(fgets(command, MAX_LINE - 1, IOchannel) == NULL)
        fatalError(ERR_IO_ERROR, 0, 0);

    /* client and server could have different line-termination */
    if(*(command + 1) == '\n' || *(command + 1) == '\r')
        {
        if(*command == 'n')
            {
            traceFlag |= TRACE_DEBUG_NEXT;
            currentLevel = recursionCount;
            break;
            }
        if(*command == 's')
            {
            traceFlag &= ~TRACE_DEBUG_NEXT;
            break;
            }
        if(*command == 'q')
            {
            closeTrace();
            longjmp(errorJump, ERR_USER_RESET);
            }
        if(*command == 'c')
            {
            closeTrace();
            break;
            }
        }

    resultStackIdxSave = resultStackIdx;
    memcpy(errorJumpSave, errorJump, sizeof(jmp_buf));
    contextSave = currentContext;
    currentContext = currentFunc->context;
    if(setjmp(errorJump))
        {
        cleanupResults(resultStackIdxSave);
        goto DEBUG_EVAL_END;
        }

    executeCommandLine(command, OUT_CONSOLE, NULL); 

    DEBUG_EVAL_END:
    currentContext = contextSave;
    memcpy(errorJump, errorJumpSave, sizeof(jmp_buf));
    }
}