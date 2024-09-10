bool CStdCrypt::getKey(BYTE *pKey, size_t cbKeyLen)
{
	if (!m_valid || cbKeyLen < sizeof(ExternalKey))
		return false;

	ExternalKey tmp = { 0 };
	memcpy(&tmp.m_key, m_key, KEY_LENGTH);
	tmp.m_crc32 = crc32(0xAbbaDead, (LPCBYTE)m_password.GetString(), m_password.GetLength());
	getRandomBytes(tmp.slack, sizeof(tmp.slack));

	BYTE tmpHash[32];
	slow_hash(m_password, m_password.GetLength(), tmpHash);

	CRijndael tmpAes;
	tmpAes.MakeKey(tmpHash, tmpAes.sm_chain0, KEY_LENGTH, BLOCK_SIZE);
	tmpAes.Encrypt(&tmp, pKey, sizeof(tmp));
	return true;
}