int
__lll_trylock_elision (int *futex, short *adapt_count)
{
    /* Implement POSIX semantics by forbiding nesting
       trylock.  Sorry.  After the abort the code is re-executed
       non transactional and if the lock was already locked
       return an error.  */
    _xabort (_ABORT_NESTED_TRYLOCK);

    /* Only try a transaction if it's worth it.  */
    if (*adapt_count <= 0)
    {
        unsigned status;

        if ((status = _xbegin()) == _XBEGIN_STARTED)
        {
            if (*futex == 0)
                return 0;

            /* Lock was busy.  Fall back to normal locking.
               Could also _xend here but xabort with 0xff code
               is more visible in the profiler.  */
            _xabort (_ABORT_LOCK_BUSY);
        }

        if (!(status & _XABORT_RETRY))
        {
            /* Internal abort.  No chance for retry.  For future
               locks don't try speculation for some time.  */
            if (*adapt_count != aconf.skip_trylock_internal_abort)
                *adapt_count = aconf.skip_trylock_internal_abort;
        }
        /* Could do some retries here.  */
    }
    else
    {
        /* Lost updates are possible, but harmless.  */
        (*adapt_count)--;
    }

    return lll_trylock (*futex);
}