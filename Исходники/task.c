/***********************************************************************
 *           TASK_CallTaskSignalProc
 */
static void TASK_CallTaskSignalProc( UINT16 uCode, HANDLE16 hTaskOrModule )
{
    WORD args[5];
    TDB *pTask = TASK_GetCurrent();

    if ( !pTask || !pTask->userhandler ) return;

    args[4] = hTaskOrModule;
    args[3] = uCode;
    args[2] = 0;
    args[1] = pTask->hInstance;
    args[0] = pTask->hQueue;
    WOWCallback16Ex( (DWORD)pTask->userhandler, WCB16_PASCAL, sizeof(args), args, NULL );
}