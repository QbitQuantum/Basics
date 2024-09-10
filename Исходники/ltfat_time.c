double ltfat_time()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    return (1000.0 * ((double)tv.tv_sec) + ((double)tv.tv_nsec) / 1000000.0);
}