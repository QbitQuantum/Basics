static jlong GTime_get_utc_time_millis(JNIEnv* env, jobject thiz)
{
   gtime_t t;
   t = gpst2utc(get_gtime_t(env, thiz));
   return (jlong)(1000ll * t.time + llround(1000.0 * t.sec));
}