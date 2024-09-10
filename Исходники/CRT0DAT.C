static void __cdecl doexit (
        int code,
        int quick,
        int retcaller
        )
{
#ifdef _DEBUG
        static int fExit = 0;
#endif  /* _DEBUG */

#ifdef _MT
        _lockexit();        /* assure only 1 thread in exit path */
#endif  /* _MT */

        if (_C_Exit_Done == TRUE)                               /* if doexit() is being called recursively */
                TerminateProcess(GetCurrentProcess(),code);     /* terminate with extreme prejudice */
        _C_Termination_Done = TRUE;

        /* save callable exit flag (for use by terminators) */
        _exitflag = (char) retcaller;  /* 0 = term, !0 = callable exit */

        if (!quick) {

            /*
             * do _onexit/atexit() terminators
             * (if there are any)
             *
             * These terminators MUST be executed in reverse order (LIFO)!
             *
             * NOTE:
             *  This code assumes that __onexitbegin points
             *  to the first valid onexit() entry and that
             *  __onexitend points past the last valid entry.
             *  If __onexitbegin == __onexitend, the table
             *  is empty and there are no routines to call.
             */

            if (__onexitbegin) {
                _PVFV * pfend = __onexitend;

                while ( --pfend >= __onexitbegin )
                /*
                 * if current table entry is non-NULL,
                 * call thru it.
                 */
                if ( *pfend != NULL )
                    (**pfend)();
            }

            /*
             * do pre-terminators
             */
            _initterm(__xp_a, __xp_z);
        }

        /*
         * do terminators
         */
        _initterm(__xt_a, __xt_z);

#ifndef CRTDLL
#ifdef _DEBUG
        /* Dump all memory leaks */
        if (!fExit && _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_LEAK_CHECK_DF)
        {
            fExit = 1;
            _CrtDumpMemoryLeaks();
        }
#endif  /* _DEBUG */
#endif  /* CRTDLL */

        /* return to OS or to caller */

        if (retcaller) {
#ifdef _MT
            _unlockexit();      /* unlock the exit code path */
#endif  /* _MT */
            return;
        }


        _C_Exit_Done = TRUE;

        ExitProcess(code);


}