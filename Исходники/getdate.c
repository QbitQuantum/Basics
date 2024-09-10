/*--------------------------------------------------------------------------*/
double *getCurrentDateAsDoubleVector(int *iErr)
{
    double *dVector = (double*) MALLOC(sizeof(double) * NB_ELEMNT_ARRAY_GETDATE);
    *iErr = 1;
    if (dVector)
    {
        struct tm *nowstruct = NULL;
        double milliseconds = 0.;
#ifdef _MSC_VER
        /* manages date  up through 23:59:59, December 31, 3000 */
        /* previous version was limited to  19:14:07 January 18, 2038, UTC. */
        __time64_t long_time;
        struct __timeb64 tstruct;
        _ftime64(&tstruct);
        long_time = tstruct.time;
        nowstruct = _localtime64(&long_time);
#else
        struct timeval timebuffer;
        gettimeofday(&timebuffer, NULL);
        nowstruct = localtime(&timebuffer);
#endif

#ifdef _MSC_VER
        milliseconds = (double)(tstruct.millitm);
#else
        milliseconds = (double)(timebuffer.tv_usec / 1000);  /* micro to ms */
#endif
        if (milliseconds < 0)
        {
            milliseconds = 0.;
        }

        if (nowstruct)
        {
            dVector[YEAR_INDEX] =           (double)(1900 + nowstruct->tm_year);
            dVector[MONTH_INDEX] =          (double)(1    + nowstruct->tm_mon);
            dVector[WEEK_NUMBER_INDEX] =    (double)(week_number(nowstruct));
            dVector[DAY_OF_YEAR_INDEX] =    (double)(1    + nowstruct->tm_yday);
            dVector[WEEKDAY_INDEX] =        (double)(1    + nowstruct->tm_wday);
            dVector[DAY_OF_MONTH_INDEX] =   (double)(nowstruct->tm_mday);
            dVector[HOUR_OF_DAY_INDEX] =    (double)(nowstruct->tm_hour);
            dVector[MINUTE_INDEX] =         (double)(nowstruct->tm_min);
            dVector[SECOND_INDEX] =         (double)(nowstruct->tm_sec);
            dVector[MILLISECOND_INDEX] =    (double)milliseconds;
            *iErr = 0;
        }
    }
    return dVector;
}