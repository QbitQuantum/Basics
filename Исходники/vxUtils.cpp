const char * CHasher::GetCheckSum(){

#if _WIN32
	DWORD cbHash = 16;
	DWORD dwStatus = 0;
	if (!CryptGetHashParam(m_cryptHash, HP_HASHVAL, m_hash, &cbHash, 0)){
		dwStatus = GetLastError();
		printf("CryptGetHashParam failed: %d\n", dwStatus);
		CryptReleaseContext(m_cryptProv, 0);
		CryptDestroyHash(m_cryptHash);
		throw - 1;
	}
#elif HAVE_OpenSSL
	if (!MD5_Final(m_hash, &m_handle)) {
		printf("ERROR: MD5_Final() failed\n");
	}
#endif
	char hex[] = "0123456789abcdef";
	for (int i = 0; i < 16; i++){
		m_checkSum[i * 2] = hex[m_hash[i] >> 4];
		m_checkSum[(i * 2) + 1] = hex[m_hash[i] & 0xF];
	}
	return m_checkSum;
}