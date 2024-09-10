__checkReturn
FLT_PREOP_CALLBACK_STATUS
FLTAPI
PreCleanup (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __out PVOID *CompletionContext
    )
{
    NTSTATUS status;
    UNREFERENCED_PARAMETER( CompletionContext );

    FLT_PREOP_CALLBACK_STATUS fltStatus = FLT_PREOP_SUCCESS_NO_CALLBACK;

    PStreamHandleContext pStreamHandleContext = NULL;
    
    __try
    {
        status = GetStreamHandleContext( FltObjects, &pStreamHandleContext );

        if ( !NT_SUCCESS( status ) )
        {
            pStreamHandleContext = NULL;

            __leave;
        }

        if ( FlagOn( pStreamHandleContext->m_Flags, _STREAM_H_FLAGS_ECPPREF ) )
        {
            __leave;
        }

        if ( !gFileMgr.m_FltSystem->IsFiltersExist() )
        {
            __leave;
        }

        VERDICT Verdict = VERDICT_NOT_FILTERED;
        FileInterceptorContext event(
            Data,
            FltObjects,
            pStreamHandleContext->m_StreamCtx,
            FILE_MINIFILTER,
            OP_FILE_CLEANUP,
            0,
            PreProcessing
            );

        PARAMS_MASK params2user;
        status = gFileMgr.m_FltSystem->FilterEvent(
            &event,
            &Verdict,
            &params2user
            );

        if ( NT_SUCCESS( status ) && FlagOn( Verdict, VERDICT_ASK ) )
        {
            status = ChannelAskUser( &event, params2user, &Verdict );
            if ( NT_SUCCESS( status ) )
            {
                if (
                    !FlagOn( Verdict, VERDICT_DENY)
                    &&
                    FlagOn( Verdict, VERDICT_CACHE1 )
                    )
                {
                    event.SetCache1();
                }
            }
        }
    }
    __finally
    {
        ReleaseContext( (PFLT_CONTEXT*) &pStreamHandleContext );
    }

    return fltStatus;
}