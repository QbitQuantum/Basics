QAttachedJNIEnv::QAttachedJNIEnv()
{
    JavaVM *vm = javaVM();
    if (vm->GetEnv((void**)&jniEnv, JNI_VERSION_1_6) == JNI_EDETACHED) {
        if (vm->AttachCurrentThread(&jniEnv, 0) < 0) {
            jniEnv = 0;
            return;
        }
    }

    if (!m_refCount.hasLocalData())
        m_refCount.setLocalData(1);
    else
        m_refCount.setLocalData(m_refCount.localData() + 1);
}