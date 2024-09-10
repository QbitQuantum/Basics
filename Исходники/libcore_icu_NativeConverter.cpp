static void NativeConverter_setCallbackDecode(JNIEnv* env, jclass, jlong address,
        jint onMalformedInput, jint onUnmappableInput, jstring javaReplacement) {
    UConverter* cnv = toUConverter(address);
    if (cnv == NULL) {
        maybeThrowIcuException(env, "toConverter", U_ILLEGAL_ARGUMENT_ERROR);
        return;
    }

    UConverterToUCallback oldCallback;
    const void* oldCallbackContext;
    ucnv_getToUCallBack(cnv, &oldCallback, &oldCallbackContext);

    DecoderCallbackContext* callbackContext = const_cast<DecoderCallbackContext*>(
            reinterpret_cast<const DecoderCallbackContext*>(oldCallbackContext));
    if (callbackContext == NULL) {
        callbackContext = new DecoderCallbackContext;
    }

    callbackContext->onMalformedInput = getToUCallback(onMalformedInput);
    callbackContext->onUnmappableInput = getToUCallback(onUnmappableInput);

    ScopedStringChars replacement(env, javaReplacement);
    if (replacement.get() == NULL) {
        maybeThrowIcuException(env, "replacement", U_ILLEGAL_ARGUMENT_ERROR);
        return;
    }
    u_strncpy(callbackContext->replacementChars, replacement.get(), replacement.size());
    callbackContext->replacementCharCount = replacement.size();

    UErrorCode errorCode = U_ZERO_ERROR;
    ucnv_setToUCallBack(cnv, CHARSET_DECODER_CALLBACK, callbackContext, NULL, NULL, &errorCode);
    maybeThrowIcuException(env, "ucnv_setToUCallBack", errorCode);
}