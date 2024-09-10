void UnprotectData(const std::vector<unsigned char>& prot, secure_buffer& data)
{
	// populate buffer with encrypted data
	secure_buffer buf(prot.begin(), prot.end());
	// set initial size
	DWORD dwBufferSize = buf.size();
	// decrypt data using session key
	if (!CryptDecrypt(SessionKey::Instance(), 0, TRUE, 0, &buf[0], &dwBufferSize))
		throw SystemError(GetLastError());
	// set actual data size
	buf.resize(dwBufferSize);
	// set result
	data.swap(buf);
}