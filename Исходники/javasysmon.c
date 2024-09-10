JNIEXPORT jint JNICALL Java_com_jezhumble_javasysmon_SolarisMonitor_currentPid (JNIEnv *env, jobject obj)
{
  return (jint) getpid();
}