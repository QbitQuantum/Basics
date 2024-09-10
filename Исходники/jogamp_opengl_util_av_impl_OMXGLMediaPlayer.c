JNIEXPORT jboolean JNICALL Java_jogamp_opengl_util_av_impl_OMXGLMediaPlayer_initIDs0
  (JNIEnv *env, jclass clazz)
{
#ifdef _WIN32_WCE
    _wfreopen(TEXT(STDOUT_FILE),L"w",stdout);
    _wfreopen(TEXT(STDERR_FILE),L"w",stderr);
#endif
    JoglCommon_init(env);

    jclass c;
    if (omxGLMediaPlayerClazz != NULL) {
        return;
    }

    c = (*env)->FindClass(env, ClazzNameOMXGLMediaPlayer);
    if(NULL==c) {
        JoglCommon_FatalError(env, "JOGL OMX: can't find %s", ClazzNameOMXGLMediaPlayer);
    }
    omxGLMediaPlayerClazz = (jclass)(*env)->NewGlobalRef(env, c);
    (*env)->DeleteLocalRef(env, c);
    if(NULL==omxGLMediaPlayerClazz) {
        JoglCommon_FatalError(env, "JOGL OMX: can't use %s", ClazzNameOMXGLMediaPlayer);
    }

    jni_mid_updateAttributes = (*env)->GetMethodID(env, omxGLMediaPlayerClazz, "updateAttributes", "(IIIIIFIILjava/lang/String;Ljava/lang/String;)V");

    if(jni_mid_updateAttributes == NULL) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}