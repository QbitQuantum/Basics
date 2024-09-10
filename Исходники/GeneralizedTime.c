static struct tm *gmtime_r(const time_t *tloc, struct tm *result) {
    struct tm *tm;
    if((tm = gmtime(tloc)))
        return memcpy(result, tm, sizeof(struct tm));
    return 0;
}