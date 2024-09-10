void __cdecl _freeptd (
        _ptiddata ptd
        )
{
        /*
         * Do nothing unless per-thread data has been allocated for this module!
         */

        if ( __flsindex != 0xFFFFFFFF ) {

            /*
             * if parameter "ptd" is NULL, get the per-thread data pointer
             * Must NOT call _getptd because it will allocate one if none exists!
             * If FLS_GETVALUE is NULL then ptd could not have been set
             */

            if ( ptd == NULL
#ifndef _M_AMD64
                 && (FLS_GETVALUE != NULL)
#endif  /* _M_AMD64 */
                )
                ptd = FLS_GETVALUE(__flsindex);

            /*
             * Zero out the one pointer to the per-thread data block
             */

            FLS_SETVALUE(__flsindex, (LPVOID)0);

            _freefls(ptd);
        }

        if ( __getvalueindex != 0xFFFFFFFF ) {
            /*
             * Zero out the FlsGetValue pointer
             */
            TlsSetValue(__getvalueindex, (LPVOID)0);
        }
}