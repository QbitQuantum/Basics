int func(void * thrd)
{
    struct timespec ts;
    timespec_get( &ts, TIME_UTC);        // The current time;
    ts.tv_sec += 3;                      // 3 seconds from now.

    printf("%s waiting ...\n", (char*)thrd);
    int res = mtx_timedlock(&mtx, &ts);
    switch(res)
    {
        case thrd_success:
           puts("Obtained mutex\n... releasing ...");
           mtx_unlock(&mtx);   break;
        case thrd_timedout:
           puts("Timed out.");   break;
        default:
           puts("mtx_timedlock: error.");
    };
    return res;
}