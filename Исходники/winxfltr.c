int __cdecl _XcptFilter (
        unsigned long xcptnum,
        PEXCEPTION_POINTERS pxcptinfoptrs
        )
{
        struct _XCPT_ACTION * pxcptact;
        _PHNDLR phandler;
        void *oldpxcptinfoptrs;
        int oldfpecode;
        int indx;

        _ptiddata ptd = _getptd_noexit();
        if (!ptd) {
            // we can't deal with it - pass it on.
            return( UnhandledExceptionFilter(pxcptinfoptrs) );
        }

        pxcptact = xcptlookup(xcptnum, ptd->_pxcptacttab);

        if (pxcptact == NULL)
        {
            phandler = SIG_DFL;
        }
        else
        {
            phandler = pxcptact->XcptAction;
        }

        /*
         * first, take care of all unrecognized exceptions and exceptions with
         * XcptAction values of SIG_DFL.
         */
        if ( phandler == SIG_DFL )

                /*
                 * pass the buck to the UnhandledExceptionFilter
                 */
                return( UnhandledExceptionFilter(pxcptinfoptrs) );


        /*
         * next, weed out all of the exceptions that need to be handled by
         * dying, perhaps with a runtime error message
         */
        if ( phandler == SIG_DIE ) {
                /*
                 * reset XcptAction (in case of recursion) and drop into the
                 * except-clause.
                 */
                pxcptact->XcptAction = SIG_DFL;
                return(EXCEPTION_EXECUTE_HANDLER);
        }

        /*
         * next, weed out all of the exceptions that are simply ignored
         */
        if ( phandler == SIG_IGN )
                /*
                 * resume execution
                 */
                return(EXCEPTION_CONTINUE_EXECUTION);

        /*
         * the remaining exceptions all correspond to C signals which have
         * signal handlers associated with them. for some, special setup
         * is required before the signal handler is called. in all cases,
         * if the signal handler returns, -1 is returned by this function
         * to resume execution at the point where the exception occurred.
         */

        /*
         * save the old value of _pxcptinfoptrs (in case this is a nested
         * exception/signal) and store the current one.
         */
        oldpxcptinfoptrs = PXCPTINFOPTRS;
        PXCPTINFOPTRS = pxcptinfoptrs;

        /*
         * call the user-supplied signal handler
         *
         * floating point exceptions must be handled specially since, from
         * the C point-of-view, there is only one signal. the exact identity
         * of the exception is passed in the global variable _fpecode.
         */
        if ( pxcptact->SigNum == SIGFPE ) {

                /*
                 * reset the XcptAction field to the default for all entries
                 * corresponding to SIGFPE.
                 */
                for ( indx = _First_FPE_Indx ;
                      indx < _First_FPE_Indx + _Num_FPE ;
                      indx++ )
                {
                        ( (struct _XCPT_ACTION *)(ptd->_pxcptacttab) +
                          indx )->XcptAction = SIG_DFL;
                }

                /*
                 * Save the current _fpecode in case it is a nested floating
                 * point exception (not clear that we need to support this,
                 * but it's easy).
                 */
                oldfpecode = FPECODE;

                /*
                 * there are no exceptions corresponding to
                 * following _FPE_xxx codes:
                 *
                 *      _FPE_UNEMULATED
                 *      _FPE_SQRTNEG
                 *
                 * futhermore, STATUS_FLOATING_STACK_CHECK is
                 * raised for both floating point stack under-
                 * flow and overflow. thus, the exception does
                 * not distinguish between _FPE_STACKOVERLOW
                 * and _FPE_STACKUNDERFLOW. arbitrarily, _fpecode
                 * is set to the former value.
                 *
                 * the following should be a switch statement but, alas, the
                 * compiler doesn't like switching on unsigned longs...
                 */
                if ( pxcptact->XcptNum == STATUS_FLOAT_DIVIDE_BY_ZERO )

                        FPECODE = _FPE_ZERODIVIDE;

                else if ( pxcptact->XcptNum == STATUS_FLOAT_INVALID_OPERATION )

                        FPECODE = _FPE_INVALID;

                else if ( pxcptact->XcptNum == STATUS_FLOAT_OVERFLOW )

                        FPECODE = _FPE_OVERFLOW;

                else if ( pxcptact->XcptNum == STATUS_FLOAT_UNDERFLOW )

                        FPECODE = _FPE_UNDERFLOW;

                else if ( pxcptact->XcptNum == STATUS_FLOAT_DENORMAL_OPERAND )

                        FPECODE = _FPE_DENORMAL;

                else if ( pxcptact->XcptNum == STATUS_FLOAT_INEXACT_RESULT )

                        FPECODE = _FPE_INEXACT;

                else if ( pxcptact->XcptNum == STATUS_FLOAT_STACK_CHECK )

                        FPECODE = _FPE_STACKOVERFLOW;

                /*
                 * call the SIGFPE handler. note the special code to support
                 * old MS-C programs whose SIGFPE handlers expect two args.
                 *
                 * NOTE: THE CAST AND CALL BELOW DEPEND ON __cdecl BEING
                 * CALLER CLEANUP!
                 */
                (*(void (__cdecl *)(int, int))phandler)(SIGFPE, FPECODE);

                /*
                 * restore the old value of _fpecode
                 */
                FPECODE = oldfpecode;
        }
        else {
                /*
                 * reset the XcptAction field to the default, then call the
                 * user-supplied handler
                 */
                pxcptact->XcptAction = SIG_DFL;
                (*phandler)(pxcptact->SigNum);
        }

        /*
         * restore the old value of _pxcptinfoptrs
         */
        PXCPTINFOPTRS = oldpxcptinfoptrs;

        return(EXCEPTION_CONTINUE_EXECUTION);

}