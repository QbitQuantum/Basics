JNIEXPORT jboolean JNICALL Java_jogamp_newt_driver_kd_WindowDriver_initIDs
  (JNIEnv *env, jclass clazz)
{
#ifdef VERBOSE_ON
    #ifdef _WIN32_WCE
        _wfreopen(TEXT(STDOUT_FILE),L"w",stdout);
        _wfreopen(TEXT(STDERR_FILE),L"w",stderr);
    #endif
#endif
    windowCreatedID = (*env)->GetMethodID(env, clazz, "windowCreated", "(J)V");
    sizeChangedID = (*env)->GetMethodID(env, clazz, "sizeChanged", "(ZIIZ)V");
    visibleChangedID = (*env)->GetMethodID(env, clazz, "visibleChanged", "(ZZ)V");
    windowDestroyNotifyID = (*env)->GetMethodID(env, clazz, "windowDestroyNotify", "(Z)Z");
    sendMouseEventID = (*env)->GetMethodID(env, clazz, "sendMouseEvent", "(SIIISF)V");
    sendKeyEventID = (*env)->GetMethodID(env, clazz, "sendKeyEvent", "(SISSC)V");
    if (windowCreatedID == NULL ||
        sizeChangedID == NULL ||
        visibleChangedID == NULL ||
        windowDestroyNotifyID == NULL ||
        sendMouseEventID == NULL ||
        sendKeyEventID == NULL) {
        DBG_PRINT( "initIDs failed\n" );
        return JNI_FALSE;
    }
    DBG_PRINT( "initIDs ok\n" );
    return JNI_TRUE;
}