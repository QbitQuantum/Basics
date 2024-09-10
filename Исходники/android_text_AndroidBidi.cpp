static jint runBidi(JNIEnv* env, jobject obj, jint dir, jcharArray chsArray, 
                    jbyteArray infoArray, int n, jboolean haveInfo)
{
    // Parameters are checked on java side
    // Failures from GetXXXArrayElements indicate a serious out-of-memory condition
    // that we don't bother to report, we're probably dead anyway.
    jint result = 0;
    jchar* chs = env->GetCharArrayElements(chsArray, NULL);
    if (chs != NULL) {
        jbyte* info = env->GetByteArrayElements(infoArray, NULL);
        if (info != NULL) {
            UErrorCode status = U_ZERO_ERROR;
            UBiDi* bidi = ubidi_openSized(n, 0, &status);
            ubidi_setPara(bidi, chs, n, dir, NULL, &status);
            if (U_SUCCESS(status)) {
                for (int i = 0; i < n; ++i) {
                  info[i] = ubidi_getLevelAt(bidi, i);
                }
                result = ubidi_getParaLevel(bidi);
            } else {
                jniThrowException(env, "java/lang/RuntimeException", NULL);
            }
            ubidi_close(bidi);

            env->ReleaseByteArrayElements(infoArray, info, 0);
        }
        env->ReleaseCharArrayElements(chsArray, chs, JNI_ABORT);
    }
    return result;
}