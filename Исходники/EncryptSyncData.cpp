bool CEncryptSyncData::InitEncryptHandle(const char * pchrPassWord)
{
	memset(m_chKeyPassWord,0,sizeof(m_chKeyPassWord));
	memcpy(m_chKeyPassWord,pchrPassWord,strlen(pchrPassWord));
	if(!CryptAcquireContext(&hCryptProv,NULL,NULL,PROV_RSA_FULL,0))
	{
		return false;
	}
	if(!CryptCreateHash(hCryptProv,CALG_MD5,0,0,&hHash))
	{
		return false;
	}
	if(!CryptHashData(hHash,(BYTE *)m_chKeyPassWord,strlen(m_chKeyPassWord),0)) 
	{
		return false;
	}
	if(!CryptDeriveKey(hCryptProv,ENCRYPT_ALGORITHM, hHash, KEYLENGTH,&hKey))
	{ 
		return false;
	}
 	CryptDestroyHash(hHash); 
	hHash = 0; 
	return true;
}