/*
 * Class:     org_apache_log4j_nt_NTEventLogAppender
 * Method:    reportEvent
 * Signature: (ILjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_apache_log4j_nt_NTEventLogAppender_reportEvent(
   JNIEnv *env, jobject java_this, jint jhandle, jstring jstr, jint priority) {
  jboolean localHandle = JNI_FALSE;
  HANDLE handle = gEventSources.getHandle(jhandle);
  if (handle == 0) {
    // Client didn't give us a handle so make a local one.
    handle = RegisterEventSourceW(NULL, L"Log4j");
    localHandle = JNI_TRUE;
  }
  
  // convert Java String to character array
  jsize msgLen = env->GetStringLength(jstr);
  jchar* msg = (jchar*) malloc((msgLen + 1) * sizeof(jchar));
  env->GetStringRegion(jstr, 0, msgLen, msg);
  msg[msgLen] = 0;
  
  // This is the only message supported by the package. It is backed by
  // a message resource which consists of just '%1' which is replaced
  // by the string we just created.
  const DWORD messageID = 0x1000;
  ReportEventW(handle, getType(priority), 
	      getCategory(priority), 
	      messageID, NULL, 1, 0, (const wchar_t**) &msg, NULL);
  
  free((void *)msg);
  if (localHandle == JNI_TRUE) {
    // Created the handle here so free it here too.
    DeregisterEventSource(handle);
  }
  return;
}