JNIEXPORT void JNICALL Java_ToUpperExample_toUpper
  (JNIEnv *env, jobject jobj, jbyteArray jBuf)
{
  jbyte *cpu_buf = env->GetByteArrayElements(jBuf, 0);
  toUpper((uint8_t *)cpu_buf);
  env->ReleaseByteArrayElements(jBuf, cpu_buf, 0);
}