int __cdecl _dup2 (
        int fh1,
        int fh2
        )
{
        ULONG dosretval;                /* o.s. return code */
        long new_osfhandle;

        /* validate file handles */
        if ( ((unsigned)fh1 >= (unsigned)_nhandle) ||
             !(_osfile(fh1) & FOPEN) ||
             ((unsigned)fh2 >= _NHANDLE_) )
        {
                /* handle out of range */
                errno = EBADF;
                _doserrno = 0;  /* not an OS error */
                return -1;
        }

        /*
         * Make sure there is an ioinfo struct corresponding to fh2.
         */
        if ( (fh2 >= _nhandle) && (extend_ioinfo_arrays(fh2) != 0) ) {
                errno = ENOMEM;
                return -1;
        }


#ifdef _MT
        /* get the two file handle locks; in order to prevent deadlock,
           get the lowest handle lock first. */
        if ( fh1 < fh2 ) {
                _lock_fh(fh1);
                _lock_fh(fh2);
        }
        else if ( fh1 > fh2 ) {
                _lock_fh(fh2);
                _lock_fh(fh1);
        }

        /*
         * Re-test and take care of case of unopened source handle. This is
         * necessary only in the multi-thread case where the file have been
         * closed by another thread before the lock was asserted, but after
         * the initial test above.
         */
        if ( !(_osfile(fh1) & FOPEN) ) {
                /*
                 * Source handle isn't open, release locks and bail out with
                 * an error. Note that the DuplicateHandle API will not
                 * detect this error since it implies that _osfhnd(fh1) ==
                 * INVALID_HANDLE_VALUE, and this is a legal HANDLE value
                 * (it's the HANDLE for the current process).
                 */
                _unlock_fh(fh1);
                _unlock_fh(fh2);
                errno = EBADF;
                _doserrno = 0;  /* not an OS error */
                return -1;
        }
#endif  /* _MT */

        /*
         * Take of the case of equal handles.
         */
        if ( fh1 == fh2 ) {
                /*
                 * Since fh1 is known to be open, return 0 indicating success.
                 * This is in conformance with the POSIX specification for
                 * dup2.
                 */
                _unlock_fh(fh1);
                _unlock_fh(fh2);
                return 0;
        }

        /*
         * if fh2 is open, close it.
         */
        if ( _osfile(fh2) & FOPEN )
                /*
                 * close the handle. ignore the possibility of an error - an
                 * error simply means that an OS handle value may remain bound
                 * for the duration of the process.  Use _close_lk as we
                 * already own lock
                 */
                (void) _close_lk(fh2);


        /* Duplicate source file onto target file */

        if ( !(DuplicateHandle(GetCurrentProcess(),
                               (HANDLE)_get_osfhandle(fh1),
                               GetCurrentProcess(),
                               (PHANDLE)&new_osfhandle,
                               0L,
                               TRUE,
                               DUPLICATE_SAME_ACCESS)) )
        {

                dosretval = GetLastError();
        }
        else {
                _set_osfhnd(fh2, new_osfhandle);
                dosretval = 0;
        }

        if (dosretval) {
                _dosmaperr(dosretval);
                _unlock_fh(fh1);
                _unlock_fh(fh2);
                return -1;
        }

        /* copy the _osfile information, with the FNOINHERIT bit cleared */
        _osfile(fh2) = _osfile(fh1) & ~FNOINHERIT;

        /* unlock file handles */
        _unlock_fh(fh1);
        _unlock_fh(fh2);

        return 0;
}