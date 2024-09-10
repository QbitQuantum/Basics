/*
 * Set an attribute.
 */
JNIEXPORT jint JNICALL GEN_FUNCNAME(Card_NativeSetAttrib)
(JNIEnv *env, jobject _this, jint jdwAttribId, jbyteArray jattr, jint jattrLen)
{
#if defined(WIN32) || defined(HAVE_SCARD_ATTRIBUTES)
    SCARDHANDLE card;
    char *cattr;
    jboolean isCopy;

    card = (SCARDHANDLE) (*env)->GetLongField(env, _this, CardField);

    cattr = (*env)->GetByteArrayElements(env, jattr, &isCopy);

    return SCardSetAttrib(card, jdwAttribId, cattr, jattrLen);
#else
    pcscex_throw(env, "Unsupported Get-/Set-Attributes on earlier PCSClite versions", 0);
    return SCARD_E_INVALID_PARAMETER;
#endif /* defined(WIN32) || defined(HAVE_SCARD_ATTRIBUTES) */
}