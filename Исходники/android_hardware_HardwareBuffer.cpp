static jint android_hardware_HardwareBuffer_getFormat(JNIEnv* env,
    jobject clazz, jlong nativeObject) {
    GraphicBuffer* buffer = GraphicBufferWrapper_to_GraphicBuffer(nativeObject);
    return static_cast<jint>(android_hardware_HardwareBuffer_convertFromPixelFormat(
            buffer->getPixelFormat()));
}