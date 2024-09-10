jstring __MIX_PREFIX_FUNC_PASTE(MIX_PREFIX_UPAPI_FUNC,decryptMessage(JNIEnv* env, jobject javaThis, jstring str_msg_in, jstring str_encryt_alg, jstring str_cert_id))
{
	char * szData = malloc(MAX_BUFFER_LEN);
	
	memset(szData, 0, MAX_BUFFER_LEN);

	if(!str_msg_in || !str_encryt_alg || !str_cert_id)
	{
		setLastErrInfo(EStateErrorInvalidArg);

		return NULL;
	}

	decryptMessage(szData, 
		(* env)->GetStringUTFChars(env, str_msg_in, 0),
		(* env)->GetStringUTFChars(env, str_encryt_alg, 0),
		atoi((* env)->GetStringUTFChars(env, str_cert_id, 0))
		);

	jstring strRet = (*env)->NewStringUTF(env, szData);

	free(szData);

	return strRet;
}