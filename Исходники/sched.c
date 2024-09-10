/**
 * Get the SCHED_RR interval.
 * @param  pid The process identifier.
 * @param  tp The SCHED_RR interval.
 * @return Always return 0.
 */
int sched_rr_get_interval(pid_t pid, struct timespec * tp)
{
    DWORD   timeAdjustment, timeIncrement;
    BOOL    isTimeAdjustmentDisabled;

    (void) GetSystemTimeAdjustment(&timeAdjustment, &timeIncrement, &isTimeAdjustmentDisabled);
    tp->tv_sec = 0;
    tp->tv_nsec = timeIncrement * 100;

    return 0;
}