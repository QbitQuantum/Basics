/*
 * Class:     org_company_security_csp_NativeCrypto
 * Method:    digestInit
 * Signature: (Lorg/company/security/csp/CSPDigest;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_company_security_csp_NativeCrypto_digestInit(
		JNIEnv *env, jclass clazz, jobject jMessageDigest, jstring jHashAlgorithm) {

	HCRYPTPROV hCryptProv = (HCRYPTPROV) NULL;
	HCRYPTHASH hCryptHash = (HCRYPTHASH) NULL;
	DWORD dwBlockSize;
	BOOL result = FALSE;

	{
		ALG_ID algId = MapHashAlgorithm(env, jHashAlgorithm);
		DWORD dwProvId;
		jclass clazzCSPDigest;
		jmethodID mCSPPublicKeyInit;

		if(! FindProviderByAlg(env, NULL, algId, &dwProvId, &dwBlockSize)) {
			goto _m_leave;
		}

		if(! CryptAcquireContext(&hCryptProv, NULL, NULL, dwProvId, CRYPT_VERIFYCONTEXT)) {
			ThrowException(env, PROVIDER_EXCEPTION, GetLastError());
			goto _m_leave;
		}

		// выделяем контекст хеш функции
		if(! CryptCreateHash(hCryptProv, algId, 0, 0, &hCryptHash)) {
			ThrowException(env, DIGEST_EXCEPTION, GetLastError());
			goto _m_leave;
		}

		// Get the method ID for the CSPPublicKey constructor
		clazzCSPDigest =
				(*env)->FindClass(env, "org/company/security/csp/CSPDigest");

		mCSPPublicKeyInit =
				(*env)->GetMethodID(env, clazzCSPDigest, "initDigest", "(JJI)V");

		// Create a new CSP public key
		(*env)->CallVoidMethod(env, jMessageDigest, mCSPPublicKeyInit,
				(jlong) hCryptProv, (jlong) hCryptHash, (jint) dwBlockSize);

		result = TRUE;
	}
	_m_leave:
	{
		if(! result) {
			if (hCryptHash)
				CryptDestroyHash((HCRYPTHASH) hCryptHash);

			if(hCryptProv)
				CryptReleaseContext((HCRYPTPROV) hCryptProv, 0);
		}
	}
}