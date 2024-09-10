static jboolean requireEnd(JNIEnv* env, jclass clazz, RegExData* data)
{
    UErrorCode status = U_ZERO_ERROR;
    jboolean result = uregex_requireEnd(data->regex, &status);
    if (!U_SUCCESS(status)) {
        throwRuntimeException(env, status);
    }
    return result;
}