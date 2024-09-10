void BranchInfo::decodeCDKey(gcString cdkey)
{
	m_szCDKey = "";

	if (cdkey.size() == 0)
		return;
	
#ifdef WIN32
	size_t outLen = 0;
	char* raw = (char*)UTIL::STRING::base64_decode(cdkey, outLen);

	std::string reg = UTIL::OS::getConfigValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography\\MachineGuid", true);
	gcString key("{0}_{1}", reg, m_ItemId.toInt64());

	DATA_BLOB db;

	db.pbData = (BYTE*)raw;
	db.cbData = outLen;

	DATA_BLOB secret;
	secret.pbData = (BYTE*)key.c_str();
	secret.cbData = key.size();

	DATA_BLOB out;

	if (CryptUnprotectData(&db, NULL, &secret, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &out))
		m_szCDKey.assign((char*)out.pbData, out.cbData);

	safe_delete(raw);
#else // TODO
	m_szCDKey = cdkey;
#endif
}