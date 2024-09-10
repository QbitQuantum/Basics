static __time64_t __cdecl _make__time64_t (
        struct tm *tb,
        int ultflag
        )
{
        __time64_t tmptm1, tmptm2, tmptm3;
        struct tm tbtemp;
        long dstbias = 0;
        long timezone = 0;

        _VALIDATE_RETURN( ( tb != NULL ), EINVAL, ( ( __time64_t )( -1 ) ) )

        /*
         * First, make sure tm_year is reasonably close to being in range.
         */
        if ( ((tmptm1 = tb->tm_year) < _BASE_YEAR - 1) || (tmptm1 > _MAX_YEAR64
          + 1) )
            goto err_mktime;


        /*
         * Adjust month value so it is in the range 0 - 11.  This is because
         * we don't know how many days are in months 12, 13, 14, etc.
         */

        if ( (tb->tm_mon < 0) || (tb->tm_mon > 11) ) {

            tmptm1 += (tb->tm_mon / 12);

            if ( (tb->tm_mon %= 12) < 0 ) {
                tb->tm_mon += 12;
                tmptm1--;
            }

            /*
             * Make sure year count is still in range.
             */
            if ( (tmptm1 < _BASE_YEAR - 1) || (tmptm1 > _MAX_YEAR64 + 1) )
                goto err_mktime;
        }

        /***** HERE: tmptm1 holds number of elapsed years *****/

        /*
         * Calculate days elapsed minus one, in the given year, to the given
         * month. Check for leap year and adjust if necessary.
         */
        tmptm2 = _days[tb->tm_mon];
        if ( _IS_LEAP_YEAR(tmptm1) && (tb->tm_mon > 1) )
                tmptm2++;

        /*
         * Calculate elapsed days since base date (midnight, 1/1/70, UTC)
         *
         *
         * 365 days for each elapsed year since 1970, plus one more day for
         * each elapsed leap year. no danger of overflow because of the range
         * check (above) on tmptm1.
         */
        tmptm3 = (tmptm1 - _BASE_YEAR) * 365 + _ELAPSED_LEAP_YEARS(tmptm1);

        /*
         * elapsed days to current month (still no possible overflow)
         */
        tmptm3 += tmptm2;

        /*
         * elapsed days to current date.
         */
        tmptm1 = tmptm3 + (tmptm2 = (__time64_t)(tb->tm_mday));

        /***** HERE: tmptm1 holds number of elapsed days *****/

        /*
         * Calculate elapsed hours since base date
         */
        tmptm2 = tmptm1 * 24;

        tmptm1 = tmptm2 + (tmptm3 = (__time64_t)tb->tm_hour);

        /***** HERE: tmptm1 holds number of elapsed hours *****/

        /*
         * Calculate elapsed minutes since base date
         */

        tmptm2 = tmptm1 * 60;

        tmptm1 = tmptm2 + (tmptm3 = (__time64_t)tb->tm_min);

        /***** HERE: tmptm1 holds number of elapsed minutes *****/

        /*
         * Calculate elapsed seconds since base date
         */

        tmptm2 = tmptm1 * 60;

        tmptm1 = tmptm2 + (tmptm3 = (__time64_t)tb->tm_sec);

        /***** HERE: tmptm1 holds number of elapsed seconds *****/

        if  ( ultflag ) {

            /*
             * Adjust for timezone. No need to check for overflow since
             * localtime() will check its arg value
             */

            __tzset();

            _ERRCHECK(_get_dstbias(&dstbias));
            _ERRCHECK(_get_timezone(&timezone));

            tmptm1 += timezone;

            /*
             * Convert this second count back into a time block structure.
             * If localtime returns NULL, return an error.
             */
            if ( _localtime64_s(&tbtemp, &tmptm1) != 0 )
                goto err_mktime;

            /*
             * Now must compensate for DST. The ANSI rules are to use the
             * passed-in tm_isdst flag if it is non-negative. Otherwise,
             * compute if DST applies. Recall that tbtemp has the time without
             * DST compensation, but has set tm_isdst correctly.
             */
            if ( (tb->tm_isdst > 0) || ((tb->tm_isdst < 0) &&
              (tbtemp.tm_isdst > 0)) ) {
                tmptm1 += dstbias;
                if ( _localtime64_s(&tbtemp, &tmptm1) != 0 )
                    goto err_mktime;
            }

        }
        else {
            if ( _gmtime64_s(&tbtemp, &tmptm1) != 0)
                goto err_mktime;
        }

        /***** HERE: tmptm1 holds number of elapsed seconds, adjusted *****/
        /*****       for local time if requested                      *****/

        *tb = tbtemp;
        return tmptm1;

err_mktime:
        /*
         * All errors come to here
         */

        errno = EINVAL;
        return (__time64_t)(-1);
}