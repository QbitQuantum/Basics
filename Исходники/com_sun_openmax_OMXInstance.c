static void _initStatics(JNIEnv *env)
{
    jclass c;
#ifdef _WIN32_WCE
    _wfreopen(TEXT(STDOUT_FILE),L"w",stdout);
    _wfreopen(TEXT(STDERR_FILE),L"w",stderr);
#endif
    fprintf(stdout, "_initstatics ..\n"); fflush(stdout); // JAU
    if (runtimeExceptionClz != NULL) {
        return;
    }

    c = (*env)->FindClass(env, ClazzNameRuntimeException);
    if(NULL==c) {
        fprintf(stdout, "FatalError: can't find %s\n", ClazzNameRuntimeException);
        (*env)->FatalError(env, ClazzNameRuntimeException);
    }
    runtimeExceptionClz = (jclass)(*env)->NewGlobalRef(env, c);
    if(NULL==runtimeExceptionClz) {
        fprintf(stdout, "FatalError: can't use %s\n", ClazzNameRuntimeException);
        (*env)->FatalError(env, ClazzNameRuntimeException);
    }
}