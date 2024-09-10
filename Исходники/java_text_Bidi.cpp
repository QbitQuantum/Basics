extern "C" jintArray Java_java_text_Bidi_ubidi_1reorderVisual(JNIEnv* env, jclass, jbyteArray javaLevels, jint length) {
    ScopedByteArrayRO levelBytes(env, javaLevels);
    if (levelBytes.get() == NULL) {
        return NULL;
    }

    const UBiDiLevel* levels = reinterpret_cast<const UBiDiLevel*>(levelBytes.get());

    UniquePtr<int[]> indexMap(new int[length]);
    ubidi_reorderVisual(levels, length, &indexMap[0]);

    jintArray result = env->NewIntArray(length);
    env->SetIntArrayRegion(result, 0, length, &indexMap[0]);
    return result;
}