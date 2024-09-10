void cProtocol132::StartEncryption(const byte * a_Key)
{
	m_Encryptor.SetKey(a_Key, 16, MakeParameters(Name::IV(), ConstByteArrayParameter(a_Key, 16))(Name::FeedbackSize(), 1));
	m_Decryptor.SetKey(a_Key, 16, MakeParameters(Name::IV(), ConstByteArrayParameter(a_Key, 16))(Name::FeedbackSize(), 1));
	m_IsEncrypted = true;
	
	// Prepare the m_AuthServerID:
	CryptoPP::SHA1 Checksum;
	AString ServerID = cRoot::Get()->GetServer()->GetServerID();
	Checksum.Update((const byte *)ServerID.c_str(), ServerID.length());
	Checksum.Update(a_Key, 16);
	Checksum.Update((const byte *)m_ServerPublicKey.c_str(), m_ServerPublicKey.length());
	byte Digest[20];
	Checksum.Final(Digest);
	DigestToJava(Digest, m_AuthServerID);
}