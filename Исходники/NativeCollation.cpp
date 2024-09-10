static void NativeCollation_setOffset(JNIEnv* env, jclass, jint address, jint offset) {
    UErrorCode status = U_ZERO_ERROR;
    ucol_setOffset(toCollationElements(address), offset, &status);
    icu4jni_error(env, status);
}