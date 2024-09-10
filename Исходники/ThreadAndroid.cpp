void Thread::AttachToJVM()
{
    if (true == IsMainThread())
        return;

    DAVA::CorePlatformAndroid *core = (DAVA::CorePlatformAndroid *)DAVA::Core::Instance();
    DAVA::AndroidSystemDelegate* delegate = core->GetAndroidSystemDelegate();
    JavaVM *vm = delegate->GetVM();
    JNIEnv *env;

    if (JNI_EDETACHED == vm->GetEnv((void**)&env, JNI_VERSION_1_6))
    {
        if (vm->AttachCurrentThread(&env, NULL)!=0)
            Logger::Error("runtime_error(Could not attach current thread to JNI)");
    }
}