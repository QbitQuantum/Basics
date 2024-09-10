/* special turnstile signal for mutexes and locks.  Wakes up only those who
 * will really be able to lock the lock.  The assumption is that everyone who
 * already can use the lock has already been woken (and is thus not in the
 * turnstile any longer).
 *
 * The stillHaveReaders parm is set to 1 if this is a convert from write to read,
 * indicating that there is still at least one reader, and we should only wake
 * up other readers.  We use it in a tricky manner: we just pretent we already woke
 * a reader, and that is sufficient to prevent us from waking a writer.
 *
 * The crit sec. csp is released before the threads are woken, but after they
 * are removed from the turnstile.  It helps ensure that we won't have a spurious
 * context swap back to us if the release performs a context swap for some reason.
 */
void osi_TSignalForMLs(osi_turnstile_t *turnp, int stillHaveReaders, CRITICAL_SECTION *csp)
{
    osi_sleepInfo_t *tsp;		/* a temp */
    osi_sleepInfo_t *nsp;		/* a temp */
    osi_queue_t *wakeupListp;	/* list of dudes to wakeup after dropping lock */
    int wokeReader;
    unsigned short *sp;
    unsigned char *cp;

    wokeReader = stillHaveReaders;
    wakeupListp = NULL;
    while(tsp = turnp->lastp) {
        /* look at each sleepInfo until we find someone we're not supposed to
         * wakeup.
         */
        if (tsp->waitFor & OSI_SLEEPINFO_W4WRITE) {
            if (wokeReader)
                break;
        }
        else
            wokeReader = 1;

        /* otherwise, we will wake this guy.  For now, remove from this list
         * and move to private one, so we can do the wakeup after releasing
         * the crit sec.
         */
        osi_QRemoveHT((osi_queue_t **) &turnp->firstp, (osi_queue_t **) &turnp->lastp, &tsp->q);

        /* do the patching required for lock obtaining */
        if (tsp->waitFor & OSI_SLEEPINFO_W4WRITE) {
            cp = (void *) tsp->value;
            (*cp) |= OSI_LOCKFLAG_EXCL;
            tsp->tidp[0] = tsp->tid;
        }
        else if (tsp->waitFor & OSI_SLEEPINFO_W4READ) {
            sp = (void *) tsp->value;
#ifdef DEBUG
            if ((*sp) < OSI_RWLOCK_THREADS)
                tsp->tidp[*sp] = tsp->tid;
#endif
            (*sp)++;
        }

        /* and add to our own list */
        tsp->q.nextp = wakeupListp;
        wakeupListp = &tsp->q;

        /* now if we woke a writer, we're done, since it is pointless
         * to wake more than one writer.
         */
        if (!wokeReader)
            break;
    }

    /* hit end, or found someone we're not supposed to wakeup */
    if (csp)
        LeaveCriticalSection(csp);

        /* finally, wakeup everyone we found.  Don't free things since the sleeper
         * will free the sleepInfo structure.
         */
	for(tsp = (osi_sleepInfo_t *) wakeupListp; tsp; tsp = nsp) {
            /* pull this out first, since *tsp *could* get freed immediately
             * after the ReleaseSemaphore, if a context swap occurs.
             */
            nsp = (osi_sleepInfo_t *) tsp->q.nextp;
            _InterlockedOr(&tsp->states, OSI_SLEEPINFO_SIGNALLED);
            ReleaseSemaphore(tsp->sema, 1, NULL);
        }
}