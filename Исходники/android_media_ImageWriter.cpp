static jint Image_getFormat(JNIEnv* env, jobject thiz) {
    ALOGV("%s", __FUNCTION__);
    GraphicBuffer* buffer;
    Image_getNativeContext(env, thiz, &buffer, NULL);
    if (buffer == NULL) {
        jniThrowException(env, "java/lang/IllegalStateException",
                "Image is not initialized");
        return 0;
    }

    return Image_getPixelFormat(env, buffer->getPixelFormat());
}