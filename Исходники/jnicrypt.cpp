JNIEXPORT jbyteArray JNICALL Java_org_eclipse_equinox_internal_security_win32_WinCrypto_windecrypt
  (JNIEnv *env, jobject obj, jbyteArray value)
{
	jsize size = env->GetArrayLength(value);
	jbyte *body = env->GetByteArrayElements(value, NULL);
	if (body == NULL)
		return NULL;

	DATA_BLOB clearText;
	DATA_BLOB encryptedText;
	encryptedText.pbData = (BYTE*) body;
	encryptedText.cbData = (DWORD) size;

	LPWSTR pDescrOut =  NULL;
	BOOL result = CryptUnprotectData(&encryptedText, &pDescrOut, NULL, NULL, NULL, 0, &clearText);

	if (pDescrOut != NULL)
		LocalFree(pDescrOut);

    // release memory allocated by Java environment
	env->ReleaseByteArrayElements(value, body, 0);

	if (result == FALSE)
		return NULL;

    jbyteArray returnArray = env->NewByteArray(clearText.cbData);
	env->SetByteArrayRegion(returnArray, 0, clearText.cbData, (jbyte*) clearText.pbData);
	LocalFree(clearText.pbData); // no need any more, have Java representation

	return returnArray;
}