CString Crytography ::Encrypt(CString mes)
{
		
		CString m_cipher;
		unsigned long length = mes.GetLength() +1;
		unsigned char * cipherBlock = (unsigned char*)malloc(length);
		memset(cipherBlock, 0, length);
		memcpy(cipherBlock, mes, length -1);	

		if (!CryptEncrypt(hKey, 0, TRUE, 0, cipherBlock, &length, length))
		{
			//dwResult = GetLastError();
			AfxMessageBox("Error CryptEncrypt() failed.", MB_OK);
			return "";
		}

		m_cipher = cipherBlock;
		//m_clear = "";

		free(cipherBlock);
		//
		return m_cipher;
}