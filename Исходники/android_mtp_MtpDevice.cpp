static jboolean
android_mtp_MtpDevice_delete_object(JNIEnv *env, jobject thiz, jint object_id)
{
    MtpDevice* device = get_device_from_object(env, thiz);
    if (device && device->deleteObject(object_id)) {
        return JNI_TRUE;
    } else {
        return JNI_FALSE;
    }
}