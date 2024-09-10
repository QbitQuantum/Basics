int32_t SpiReadAutoReceiveBufferCallbackStore::performCallback(
    const char* name, uint32_t* buffer, int32_t numToRead) {
  JNIEnv* env;
  JavaVM* vm = sim::GetJVM();
  bool didAttachThread = false;
  int tryGetEnv = vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
  if (tryGetEnv == JNI_EDETACHED) {
    // Thread not attached
    didAttachThread = true;
    if (vm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr) != 0) {
      // Failed to attach, log and return
      wpi::outs() << "Failed to attach\n";
      wpi::outs().flush();
      return -1;
    }
  } else if (tryGetEnv == JNI_EVERSION) {
    wpi::outs() << "Invalid JVM Version requested\n";
    wpi::outs().flush();
  }

  auto toCallbackArr = MakeJIntArray(
      env, wpi::ArrayRef<uint32_t>{buffer, static_cast<size_t>(numToRead)});

  jint ret = env->CallIntMethod(m_call, sim::GetBufferCallback(),
                                MakeJString(env, name), toCallbackArr,
                                (jint)numToRead);

  jint* fromCallbackArr = reinterpret_cast<jint*>(
      env->GetPrimitiveArrayCritical(toCallbackArr, nullptr));

  for (int i = 0; i < ret; i++) {
    buffer[i] = fromCallbackArr[i];
  }

  env->ReleasePrimitiveArrayCritical(toCallbackArr, fromCallbackArr, JNI_ABORT);

  if (env->ExceptionCheck()) {
    env->ExceptionDescribe();
  }

  if (didAttachThread) {
    vm->DetachCurrentThread();
  }
  return ret;
}