// sets diffTimeMs parameter as well (appalling...)
bool waitingTooLong(struct timespec startTime, int threshold, time_t* diffTimeMs)
{
    struct timespec endTime;
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    *diffTimeMs = timespecToMs(diffTime(endTime, startTime));
    if(*diffTimeMs > threshold)
        return true;
    return false;
}