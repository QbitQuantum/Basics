int64_t
PRMJ_Now(void)
{
    static int nCalls = 0;
    long double lowresTime, highresTimerValue;
    FILETIME ft;
    LARGE_INTEGER now;
    bool calibrated = false;
    bool needsCalibration = false;
    int64_t returnedTime;
    long double cachedOffset = 0.0;

    /* For non threadsafe platforms, NowInit is not necessary */
#ifdef JS_THREADSAFE
    PR_CallOnce(&calibrationOnce, NowInit);
#endif
    do {
        if (!calibration.calibrated || needsCalibration) {
            MUTEX_LOCK(&calibration.calibration_lock);
            MUTEX_LOCK(&calibration.data_lock);

            /* Recalibrate only if no one else did before us */
            if(calibration.offset == cachedOffset) {
                /* Since calibration can take a while, make any other
                   threads immediately wait */
                MUTEX_SETSPINCOUNT(&calibration.data_lock, 0);

                NowCalibrate();

                calibrated = true;

                /* Restore spin count */
                MUTEX_SETSPINCOUNT(&calibration.data_lock, DATALOCK_SPINCOUNT);
            }
            MUTEX_UNLOCK(&calibration.data_lock);
            MUTEX_UNLOCK(&calibration.calibration_lock);
        }


        /* Calculate a low resolution time */
        GetSystemTimeAsFileTime(&ft);
        lowresTime = 0.1*(long double)(FILETIME2INT64(ft) - win2un);

        if (calibration.freq > 0.0) {
            long double highresTime, diff;

            DWORD timeAdjustment, timeIncrement;
            BOOL timeAdjustmentDisabled;

            /* Default to 15.625 ms if the syscall fails */
            long double skewThreshold = 15625.25;
            /* Grab high resolution time */
            QueryPerformanceCounter(&now);
            highresTimerValue = (long double)now.QuadPart;

            MUTEX_LOCK(&calibration.data_lock);
            highresTime = calibration.offset + PRMJ_USEC_PER_SEC*
                 (highresTimerValue-calibration.timer_offset)/calibration.freq;
            cachedOffset = calibration.offset;

            /* On some dual processor/core systems, we might get an earlier time
               so we cache the last time that we returned */
            calibration.last = js::Max(calibration.last, int64_t(highresTime));
            returnedTime = calibration.last;
            MUTEX_UNLOCK(&calibration.data_lock);

            /* Rather than assume the NT kernel ticks every 15.6ms, ask it */
            if (GetSystemTimeAdjustment(&timeAdjustment,
                                        &timeIncrement,
                                        &timeAdjustmentDisabled)) {
                if (timeAdjustmentDisabled) {
                    /* timeAdjustment is in units of 100ns */
                    skewThreshold = timeAdjustment/10.0;
                } else {
                    /* timeIncrement is in units of 100ns */
                    skewThreshold = timeIncrement/10.0;
                }
            }

            /* Check for clock skew */
            diff = lowresTime - highresTime;

            /* For some reason that I have not determined, the skew can be
               up to twice a kernel tick. This does not seem to happen by
               itself, but I have only seen it triggered by another program
               doing some kind of file I/O. The symptoms are a negative diff
               followed by an equally large positive diff. */
            if (mozilla::Abs(diff) > 2 * skewThreshold) {
                /*fprintf(stderr,"Clock skew detected (diff = %f)!\n", diff);*/

                if (calibrated) {
                    /* If we already calibrated once this instance, and the
                       clock is still skewed, then either the processor(s) are
                       wildly changing clockspeed or the system is so busy that
                       we get switched out for long periods of time. In either
                       case, it would be infeasible to make use of high
                       resolution results for anything, so let's resort to old
                       behavior for this call. It's possible that in the
                       future, the user will want the high resolution timer, so
                       we don't disable it entirely. */
                    returnedTime = int64_t(lowresTime);
                    needsCalibration = false;
                } else {
                    /* It is possible that when we recalibrate, we will return a
                       value less than what we have returned before; this is
                       unavoidable. We cannot tell the different between a
                       faulty QueryPerformanceCounter implementation and user
                       changes to the operating system time. Since we must
                       respect user changes to the operating system time, we
                       cannot maintain the invariant that Date.now() never
                       decreases; the old implementation has this behavior as
                       well. */
                    needsCalibration = true;
                }
            } else {
                /* No detectable clock skew */
                returnedTime = int64_t(highresTime);
                needsCalibration = false;
            }
        } else {
            /* No high resolution timer is available, so fall back */
            returnedTime = int64_t(lowresTime);
        }
    } while (needsCalibration);

    return returnedTime;
}