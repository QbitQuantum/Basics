    static JNIEnv* getJNIEnv(void)
    {

        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm)
        {
            LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
            return NULL;
        }

        JNIEnv *env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**) &env, JNI_VERSION_1_4);

        switch (ret)
        {
        case JNI_OK:
            // Success!
            return env;

        case JNI_EDETACHED:
            // Thread not attached

            // TODO : If calling AttachCurrentThread() on a native thread
            // must call DetachCurrentThread() in future.
            // see: http://developer.android.com/guide/practices/design/jni.html

            if (jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                return NULL;
            }
            else
            {
                // Success : Attached and obtained JNIEnv!
                return env;
            }

        case JNI_EVERSION:
            // Cannot recover from this error
            LOGD("JNI interface version 1.4 not supported");
        default:
            LOGD("Failed to get the environment using GetEnv()");
            return NULL;
        }
    }