void
cairo_perf_yield (void)
{
    /* try to deactivate this thread until the scheduler calls it again */

#if defined(__OS2__)
    DosSleep (0);
#elif defined(_WIN32)
    SleepEx(0, TRUE);
#elif defined(_POSIX_PRIORITY_SCHEDULING)
    sched_yield ();
#else
    sleep (0);
#endif
}