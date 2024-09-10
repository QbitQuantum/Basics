static void NativeDecimalFormat_setSymbol(JNIEnv* env, jclass, jlong addr, jint javaSymbol, jstring javaValue) {
    ScopedStringChars value(env, javaValue);
    if (value.get() == NULL) {
        return;
    }
    UErrorCode status = U_ZERO_ERROR;
    UNumberFormatSymbol symbol = static_cast<UNumberFormatSymbol>(javaSymbol);
    unum_setSymbol(toUNumberFormat(addr), symbol, value.get(), value.size(), &status);
    maybeThrowIcuException(env, "unum_setSymbol", status);
}