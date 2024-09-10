/*********************加密*********************/
JNIEXPORT jint JNICALL Java_com_softtanck_tanck_aes_utils_AesUtils_Encrypt(JNIEnv *env,
                                                                           jclass thiz,
                                                                           jbyteArray msg,
                                                                           jbyteArray key,
                                                                           jbyteArray cipher,
                                                                           jint length) {
    jbyte *pMsg = (jbyte *) (*env)->GetByteArrayElements(env, msg, 0);
    jbyte *pKey = (jbyte *) (*env)->GetByteArrayElements(env, key, 0);
    jbyte *pCipher = (jbyte *) (*env)->GetByteArrayElements(env, cipher, 0);

    if (!pMsg || !pKey || !pCipher) {
        return -1;
    }
    int flag = Encrypt(pMsg, pKey, pCipher, length); //加密函数
    (*env)->ReleaseByteArrayElements(env, msg, pMsg, 0);
    (*env)->ReleaseByteArrayElements(env, key, pKey, 0);
    (*env)->ReleaseByteArrayElements(env, cipher, pCipher, 0);
    return flag;
}