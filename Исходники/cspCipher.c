/*
 * Class:     org_company_security_csp_NativeCrypto
 * Method:    encryptDecrypt
 * Signature: ([BIJJZ)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_company_security_csp_NativeCrypto_encryptDecrypt(
		JNIEnv *env, jclass clazz,
		jbyteArray jData, jint jDataOffset, jint jDataSize,
		jlong hKey, jboolean doEncrypt, jboolean doFinal,
		jint jPaddingLength) {
	jbyteArray result = NULL;
	jbyte* pData = NULL;
	DWORD dwDataLen = (DWORD) jDataSize;
	DWORD dwBufLen = dwDataLen;
	DWORD i;
	BYTE tmp;
	HCRYPTKEY hDuplicateKey = (HCRYPTKEY) NULL;
	DWORD dwOffset;

	{
		if (! CryptDuplicateKey(hKey, NULL, 0, &hDuplicateKey)) {
#ifdef DEBUG
			fprintf(stderr, "error CryptDuplicateKey\n");
#endif
			ThrowException(env, INVALID_KEY_EXCEPTION, GetLastError());
			goto _m_leave;
		}

		if(jPaddingLength <= 0)
			jPaddingLength = 512;

		dwOffset = dwDataLen % jPaddingLength;
		if(dwOffset)
			dwBufLen = dwDataLen - dwOffset + jPaddingLength;

		// Copy data from Java buffer to native buffer
		pData = (jbyte*) malloc(dwBufLen);
		(*env)->GetByteArrayRegion(env, jData, jDataOffset, jDataSize, pData);

		if (doEncrypt == JNI_TRUE) {
			// encrypt
			if (! CryptEncrypt((HCRYPTKEY) hDuplicateKey, 0, doFinal, 0, (BYTE *)pData,
							&dwDataLen, dwBufLen)) {

#ifdef DEBUG
				fprintf(stderr, "error CryptEncrypt %x\n", GetLastError());
#endif
				ThrowException(env, INVALID_KEY_EXCEPTION, GetLastError());
				goto _m_leave;
			}
			dwBufLen = dwDataLen;

			// convert from little-endian
			for (i = 0; i < dwBufLen / 2; i++) {
				tmp = pData[i];
				pData[i] = pData[dwBufLen - i -1];
				pData[dwBufLen - i - 1] = tmp;
			}
		} else {
			// convert to little-endian
			for (i = 0; i < dwBufLen / 2; i++) {
				tmp = pData[i];
				pData[i] = pData[dwBufLen - i -1];
				pData[dwBufLen - i - 1] = tmp;
			}

			// decrypt
			if (! CryptDecrypt((HCRYPTKEY) hKey, 0, TRUE, 0, (BYTE *)pData, &dwBufLen)) {

#ifdef DEBUG
				fprintf(stderr, "error CryptDecrypt %x\n", GetLastError());
#endif
				ThrowException(env, INVALID_KEY_EXCEPTION, GetLastError());
				goto _m_leave;
			}
		}

		// Create new byte array
		result = (*env)->NewByteArray(env, dwBufLen);

		// Copy data from native buffer to Java buffer
		(*env)->SetByteArrayRegion(env, result, 0, dwBufLen, (jbyte*) pData);
	}
	_m_leave:
	{
		if (pData)
			free(pData);

		if (hDuplicateKey)
			CryptDestroyKey(hDuplicateKey);
	}

	return result;
}