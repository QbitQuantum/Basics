static int mm_start_timer(struct qemu_alarm_timer *t)
{
    timeGetDevCaps(&mm_tc, sizeof(mm_tc));

    timeBeginPeriod(mm_tc.wPeriodMin);

    mm_timer = timeSetEvent(mm_tc.wPeriodMin,   /* interval (ms) */
                            mm_tc.wPeriodMin,   /* resolution */
                            mm_alarm_handler,   /* function */
                            (DWORD_PTR)t,       /* parameter */
                            TIME_ONESHOT | TIME_CALLBACK_FUNCTION);

    if (!mm_timer) {
        fprintf(stderr, "Failed to initialize win32 alarm timer\n");
        timeEndPeriod(mm_tc.wPeriodMin);
        return -1;
    }

    return 0;
}