bool MessageQueue::raiseAndClearException(JNIEnv* env, const char* msg) {
    if (env->ExceptionCheck()) {
        jthrowable exceptionObj = env->ExceptionOccurred();
        env->ExceptionClear();
        raiseException(env, msg, exceptionObj);
        env->DeleteLocalRef(exceptionObj);
        return true;
    }
    return false;
}