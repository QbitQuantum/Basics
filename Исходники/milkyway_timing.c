static UINT mwGetMinTimerResolution(void)
{
    TIMECAPS tc;

    if (timeGetDevCaps(&tc, sizeof(tc)) != TIMERR_NOERROR)
    {
        mw_printf("Failed to get timer resolution\n");
        return 0;
    }

    /* target 1-millisecond target resolution */
    return MIN(MAX(tc.wPeriodMin, 1), tc.wPeriodMax);
}