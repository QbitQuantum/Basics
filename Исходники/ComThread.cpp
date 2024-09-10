JNIEXPORT void JNICALL Java_com_jacob2_com_ComThread_doCoInitialize
  (JNIEnv *env, jclass cls, jint mode)
{
  int threadModel = mode;
  CoInitializeEx(NULL, threadModel);
}