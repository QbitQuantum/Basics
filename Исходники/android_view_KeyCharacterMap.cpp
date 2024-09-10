static void nativeWriteToParcel(JNIEnv* env, jobject clazz, jlong ptr, jobject parcelObj) {
    NativeKeyCharacterMap* map = reinterpret_cast<NativeKeyCharacterMap*>(ptr);
    Parcel* parcel = parcelForJavaObject(env, parcelObj);
    if (parcel) {
        parcel->writeInt32(map->getDeviceId());
        map->getMap()->writeToParcel(parcel);
    }
}