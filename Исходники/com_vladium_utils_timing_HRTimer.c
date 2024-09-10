JNIEXPORT jboolean JNICALL
Java_com_vladium_utils_timing_HRTimer_timeBeginPeriod (JNIEnv * e, jclass cls, jint ms)
{
	MMRESULT result = timeBeginPeriod(ms);
    return result == TIMERR_NOERROR;
}