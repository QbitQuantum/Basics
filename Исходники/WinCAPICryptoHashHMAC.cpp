unsigned int WinCAPICryptoHashHMAC::finish(unsigned char * hash,
									   unsigned int maxLength) {

	DWORD retLen;
	BOOL fResult;

	retLen = XSEC_MAX_HASH_SIZE;

	fResult = CryptGetHashParam(
		m_h,
		HP_HASHVAL,
		m_mdValue,
		&retLen,
		0);

	if (fResult == 0) {
		throw XSECCryptoException(XSECCryptoException::MDError,
			"WinCAPI:Hash - Error getting hash value"); 
	}

	// Perform the opad operation
	HCRYPTHASH h;
	fResult = CryptCreateHash(
		m_p,
		m_algId,
		0,
		0,
		&h);

	if (fResult == 0 || h == 0) {
		throw XSECCryptoException(XSECCryptoException::MDError,
			"WinCAPI:Hash::finish - Error creating hash object for opad operation"); 
	}

	fResult = CryptHashData(
		h,
		m_opadKeyed,
		m_blockSize,
		0);

	if (fResult == 0 || h == 0) {
		if (h)
			CryptDestroyHash(h);
		throw XSECCryptoException(XSECCryptoException::MDError,
			"WinCAPI:Hash::finish - Error hashing opad data"); 
	}

	fResult = CryptHashData(
		h,
		m_mdValue,
		retLen,
		0);

	if (fResult == 0 || h == 0) {
		if (h)
			CryptDestroyHash(h);
		throw XSECCryptoException(XSECCryptoException::MDError,
			"WinCAPI:Hash::finish - Error hashing ipad hash to opad"); 
	}

	// Read out the final hash
	retLen = XSEC_MAX_HASH_SIZE;

	fResult = CryptGetHashParam(
		h,
		HP_HASHVAL,
		m_mdValue,
		&retLen,
		0);

	CryptDestroyHash(h);

	m_mdLen = retLen;
	retLen = (maxLength > m_mdLen ? m_mdLen : maxLength);
	memcpy(hash, m_mdValue, retLen);

	return (unsigned int) retLen;

}