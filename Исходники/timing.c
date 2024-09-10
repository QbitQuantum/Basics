/*
 * Call to run any timers whose time has reached the present.
 * Returns the time (in ticks) expected until the next timer after
 * that triggers.
 */
int run_timers(long anow, long *next)
{
    struct timer *first;

    init_timers();

#ifdef TIMING_SYNC
    /*
     * In this ifdef I put some code which deals with the
     * possibility that `anow' disagrees with GETTICKCOUNT by a
     * significant margin. Our strategy for dealing with it differs
     * depending on platform, because on some platforms
     * GETTICKCOUNT is more likely to be right whereas on others
     * `anow' is a better gold standard.
     */
    {
	long tnow = GETTICKCOUNT();

	if (tnow + TICKSPERSEC/50 - anow < 0 ||
	    anow + TICKSPERSEC/50 - tnow < 0
	    ) {
#if defined TIMING_SYNC_ANOW
	    /*
	     * If anow is accurate and the tick count is wrong,
	     * this is likely to be because the tick count is
	     * derived from the system clock which has changed (as
	     * can occur on Unix). Therefore, we resolve this by
	     * inventing an offset which is used to adjust all
	     * future output from GETTICKCOUNT.
	     * 
	     * A platform which defines TIMING_SYNC_ANOW is
	     * expected to have also defined this offset variable
	     * in (its platform-specific adjunct to) putty.h.
	     * Therefore we can simply reference it here and assume
	     * that it will exist.
	     */
	    tickcount_offset += anow - tnow;
#elif defined TIMING_SYNC_TICKCOUNT
	    /*
	     * If the tick count is more likely to be accurate, we
	     * simply use that as our time value, which may mean we
	     * run no timers in this call (because we got called
	     * early), or alternatively it may mean we run lots of
	     * timers in a hurry because we were called late.
	     */
	    anow = tnow;
#else
/*
 * Any platform which defines TIMING_SYNC must also define one of the two
 * auxiliary symbols TIMING_SYNC_ANOW and TIMING_SYNC_TICKCOUNT, to
 * indicate which measurement to trust when the two disagree.
 */
#error TIMING_SYNC definition incomplete
#endif
	}
    }
#endif

    now = anow;

    while (1) {
	first = (struct timer *)index234(timers, 0);

	if (!first)
	    return FALSE;	       /* no timers remaining */

	if (find234(timer_contexts, first->ctx, NULL) == NULL) {
	    /*
	     * This timer belongs to a context that has been
	     * expired. Delete it without running.
	     */
	    delpos234(timers, 0);
	    sfree(first);
	} else if (first->now - now <= 0) {
	    /*
	     * This timer is active and has reached its running
	     * time. Run it.
	     */
	    delpos234(timers, 0);
	    first->fn(first->ctx, first->now);
	    sfree(first);
	} else {
	    /*
	     * This is the first still-active timer that is in the
	     * future. Return how long it has yet to go.
	     */
	    *next = first->now;
	    return TRUE;
	}
    }
}