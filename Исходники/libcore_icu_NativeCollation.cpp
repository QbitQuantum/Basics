static void NativeCollation_setOffset(JNIEnv* env, jclass, jlong address, jint offset) {
    UErrorCode status = U_ZERO_ERROR;
    ucol_setOffset(toCollationElements(address), offset, &status);
    maybeThrowIcuException(env, "ucol_setOffset", status);
}