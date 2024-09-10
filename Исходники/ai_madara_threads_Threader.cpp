/*
 * Class:     ai_madara_threads_Threader
 * Method:    jni_terminateThread
 * Signature: (JLjava/lang/String;)V
 */
void JNICALL Java_ai_madara_threads_Threader_jni_1terminateThread(
    JNIEnv* env, jobject, jlong cptr, jstring name)
{
  Threader* current = (Threader*)cptr;

  if (current)
  {
    const char* str_name = env->GetStringUTFChars(name, 0);

    current->terminate(str_name);

    env->ReleaseStringUTFChars(name, str_name);
  }
  else
  {
    // user has tried to use a deleted object. Clean up and throw

    madara::utility::java::throw_dead_obj_exception(env,
        "Threader::terminateThread: "
        "Threader object is released already");
  }
}