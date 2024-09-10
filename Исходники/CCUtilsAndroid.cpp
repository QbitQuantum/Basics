JNIEnv* CCUtilsAndroid::getJNIEnv() {
    JavaVM* vm = JniHelper::getJavaVM();
    JNIEnv* env = NULL;
    if(vm) {
        jint ret = vm->GetEnv((void**) &env, JNI_VERSION_1_4);
        if (ret != JNI_OK) {
            jint status = vm->AttachCurrentThread(&env, NULL);
            if(status < 0) {
                CCLOGERROR("getJNIEnv: failed to attach current thread");
                env = NULL;
            }
        }
    }
    
    return env;
}