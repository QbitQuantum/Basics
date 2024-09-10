// This is the harder trick:  Pull the current state out of mid-air.
static unpacker* get_unpacker() {
  //fprintf(stderr, "get_unpacker()\n");
  JavaVM* vm = null;
  JNI_GetCreatedJavaVMs(&vm, 1, null);
  void* envRaw = null;
  vm->GetEnv(&envRaw, JNI_VERSION_1_1);
  JNIEnv* env = (JNIEnv*) envRaw;
  //fprintf(stderr, "get_unpacker() env=%p\n", env);
  if (env == null)
    return null;
  jobject pObj = env->CallStaticObjectMethod(NIclazz, currentInstMID);
  //fprintf(stderr, "get_unpacker() pObj=%p\n", pObj);
  if (pObj == null)
    return null;
  // Got pObj and env; now do it the easy way.
  return get_unpacker(env, pObj);
}