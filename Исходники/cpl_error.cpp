void    CPLErrorV(CPLErr eErrClass, int err_no, const char *fmt, va_list args )
{
    CPLErrorContext *psCtx = CPLGetErrorContext();

/* -------------------------------------------------------------------- */
/*      Expand the error message                                        */
/* -------------------------------------------------------------------- */
#if defined(HAVE_VSNPRINTF)
    {
        int nPR;
        va_list wrk_args;

#ifdef va_copy
        va_copy( wrk_args, args );
#else
        wrk_args = args;
#endif

        while( ((nPR = vsnprintf( psCtx->szLastErrMsg, 
                                 psCtx->nLastErrMsgMax, fmt, wrk_args )) == -1
                || nPR >= psCtx->nLastErrMsgMax-1)
               && psCtx->nLastErrMsgMax < 1000000 )
        {
#ifdef va_copy
            va_end( wrk_args );
            va_copy( wrk_args, args );
#else
            wrk_args = args;
#endif
            psCtx->nLastErrMsgMax *= 3;
            psCtx = (CPLErrorContext *) 
                CPLRealloc(psCtx, sizeof(CPLErrorContext) - DEFAULT_LAST_ERR_MSG_SIZE + psCtx->nLastErrMsgMax + 1);
            CPLSetTLS( CTLS_ERRORCONTEXT, psCtx, TRUE );
        }

        va_end( wrk_args );
    }
#else
    vsprintf( psCtx->szLastErrMsg, fmt, args);
#endif

/* -------------------------------------------------------------------- */
/*      If the user provided his own error handling function, then      */
/*      call it, otherwise print the error to stderr and return.        */
/* -------------------------------------------------------------------- */
    psCtx->nLastErrNo = err_no;
    psCtx->eLastErrType = eErrClass;

    if( CPLGetConfigOption("CPL_LOG_ERRORS",NULL) != NULL )
        CPLDebug( "CPLError", "%s", psCtx->szLastErrMsg );

/* -------------------------------------------------------------------- */
/*      Invoke the current error handler.                               */
/* -------------------------------------------------------------------- */
    if( psCtx->psHandlerStack != NULL )
    {
        psCtx->psHandlerStack->pfnHandler(eErrClass, err_no, 
                                          psCtx->szLastErrMsg);
    }
    else
    {
        CPLMutexHolderD( &hErrorMutex );
        if( pfnErrorHandler != NULL )
            pfnErrorHandler(eErrClass, err_no, psCtx->szLastErrMsg);
    }

    if( eErrClass == CE_Fatal )
        abort();
}