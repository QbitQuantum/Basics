static jint android_view_MotionEvent_nativeGetDeviceId(JNIEnv* env, jclass clazz,
        jint nativePtr) {
    MotionEvent* event = reinterpret_cast<MotionEvent*>(nativePtr);
    return event->getDeviceId();
}