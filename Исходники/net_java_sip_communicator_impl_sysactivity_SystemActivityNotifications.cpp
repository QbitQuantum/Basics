/*
 * Class:     net_java_sip_communicator_impl_sysactivity_SystemActivityNotifications
 * Method:    stop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_net_java_sip_communicator_impl_sysactivity_SystemActivityNotifications_stop
(JNIEnv* jniEnv, jclass clazz, jlong ptr)
{
    CancelIPChangeNotify(&overlap);
}