Jvm::Env::Env(bool daemon)
  : env(NULL), detach(false)
{
  JavaVM* jvm = Jvm::get()->jvm;

  // First check if we are already attached.
  int result = jvm->GetEnv(JNIENV_CAST(&env), Jvm::get()->version);

  // If we're not attached, attach now.
  if (result == JNI_EDETACHED) {
    if (daemon) {
      jvm->AttachCurrentThreadAsDaemon(JNIENV_CAST(&env), NULL);
    } else {
      jvm->AttachCurrentThread(JNIENV_CAST(&env), NULL);
    }
    detach = true;
  }
}