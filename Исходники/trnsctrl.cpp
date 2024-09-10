extern "C" void __cdecl _UnwindNestedFrames(
    EHRegistrationNode  *pFrame,            // Unwind up to (but not including) this frame
    EHExceptionRecord   *pExcept,           // The exception that initiated this unwind
    CONTEXT             *pContext,           // Context info for current exception
    EHRegistrationNode  *pEstablisher,
    void                *Handler,
    __ehstate_t         TargetUnwindState,
    FuncInfo            *pFuncInfo,
    DispatcherContext   *pDC,
    BOOLEAN             recursive

) {
    static const EXCEPTION_RECORD ExceptionTemplate = // A generic exception record
    {
        STATUS_UNWIND_CONSOLIDATE,         // STATUS_UNWIND_CONSOLIDATE
        EXCEPTION_NONCONTINUABLE,          // Exception flags (we don't do resume)
        nullptr,                           // Additional record (none)
        nullptr,                           // Address of exception (OS fills in)
        15,                                // Number of parameters
        {   EH_MAGIC_NUMBER1,              // Our version control magic number
            0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0
        }                                  // pThrowInfo
    };

    CONTEXT Context;
    EXCEPTION_RECORD ExceptionRecord = ExceptionTemplate;
    ExceptionRecord.ExceptionInformation[0] = (ULONG_PTR)__CxxCallCatchBlock;
                // Address of call back function
    ExceptionRecord.ExceptionInformation[1] = (ULONG_PTR)pEstablisher;
                // Used by callback funciton
    ExceptionRecord.ExceptionInformation[2] = (ULONG_PTR)Handler;
                // Used by callback function to call catch block
    ExceptionRecord.ExceptionInformation[3] = (ULONG_PTR)TargetUnwindState;
                // Used by CxxFrameHandler to unwind to target_state
    ExceptionRecord.ExceptionInformation[4] = (ULONG_PTR)pContext;
                // used to set pCurrentExContext in callback function
    ExceptionRecord.ExceptionInformation[5] = (ULONG_PTR)pFuncInfo;
                // Used in callback function to set state on stack to -2
    ExceptionRecord.ExceptionInformation[6] = (ULONG_PTR)pExcept;
                // Used for passing current Exception
    ExceptionRecord.ExceptionInformation[7] = (ULONG_PTR)recursive;
                // Used for translated Exceptions
    ExceptionRecord.ExceptionInformation[8] = EH_MAGIC_NUMBER1;
                // Used in __InternalCxxFrameHandler to detected if it's being
                // called from _UnwindNestedFrames.
    RtlUnwindEx((void *)*pFrame,
                (void *)pDC->ControlPc,    // Address where control left function
                &ExceptionRecord,
                nullptr,
                &Context,
                (PUNWIND_HISTORY_TABLE)pDC->HistoryTable);
}