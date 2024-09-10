bool CRemoteProtocolHandler::readHash(const wxString& password, wxUint32 random)
{
	if (m_type != RPHT_HASH)
		return false;

	unsigned char* hash = m_inBuffer + 3U;

	unsigned int len = password.Len() + sizeof(wxUint32);
	unsigned char*  in = new unsigned char[len];
	unsigned char* out = new unsigned char[32U];

	::memcpy(in, &random, sizeof(wxUint32));
	for (unsigned int i = 0U; i < password.Len(); i++)
		in[i + sizeof(unsigned int)] = password.GetChar(i);

	CSHA256 sha256;
	sha256.buffer(in, len, out);

	bool res = ::memcmp(out, hash, 32U) == 0;

	delete[] in;
	delete[] out;

	return res;
}