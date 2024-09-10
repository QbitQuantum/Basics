jobject android_view_InputDevice_create(JNIEnv* env, const InputDeviceInfo& deviceInfo) {
    ScopedLocalRef<jstring> nameObj(env, env->NewStringUTF(deviceInfo.getDisplayName().string()));
    if (!nameObj.get()) {
        return NULL;
    }

    ScopedLocalRef<jstring> descriptorObj(env,
            env->NewStringUTF(deviceInfo.getIdentifier().descriptor.string()));
    if (!descriptorObj.get()) {
        return NULL;
    }

    ScopedLocalRef<jobject> kcmObj(env,
            android_view_KeyCharacterMap_create(env, deviceInfo.getId(),
            deviceInfo.getKeyCharacterMap()));
    if (!kcmObj.get()) {
        return NULL;
    }

    ScopedLocalRef<jobject> inputDeviceObj(env, env->NewObject(gInputDeviceClassInfo.clazz,
            gInputDeviceClassInfo.ctor, deviceInfo.getId(), deviceInfo.getGeneration(),
            nameObj.get(), descriptorObj.get(), deviceInfo.isExternal(),
            deviceInfo.getSources(), deviceInfo.getKeyboardType(),
            kcmObj.get(), deviceInfo.hasVibrator()));

    const Vector<InputDeviceInfo::MotionRange>& ranges = deviceInfo.getMotionRanges();
    for (size_t i = 0; i < ranges.size(); i++) {
        const InputDeviceInfo::MotionRange& range = ranges.itemAt(i);
        env->CallVoidMethod(inputDeviceObj.get(), gInputDeviceClassInfo.addMotionRange, range.axis,
                range.source, range.min, range.max, range.flat, range.fuzz, range.resolution);
        if (env->ExceptionCheck()) {
            return NULL;
        }
    }

    return env->NewLocalRef(inputDeviceObj.get());
}