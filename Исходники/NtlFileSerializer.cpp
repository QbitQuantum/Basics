bool CNtlFileSerializer::LoadFile(char* pszBuffer, int nSize, bool bCrypt /*= FALSE*/, char* szCryptPassword /*= NULL*/)
{
	if ( NULL == pszBuffer )
	{
		return false;
	}

	if ( nSize == 0 )
	{
		return false;
	}

	Refresh();
	CheckInBuffer( nSize );

	if ( bCrypt )
	{
		CNtlCipher cipher;
		cipher.SetKey( DES_CIPHER, szCryptPassword, (int)strlen(szCryptPassword) );

		int nDecSize = cipher.Decrypt( pszBuffer, nSize, m_pBuffer, nSize );

		if ( nDecSize <= 0 )
		{
			return false;
		}

		IncrementEndPointer( nDecSize );
	}
	else
	{
		memcpy( (void*)(GetData()), pszBuffer, nSize );

		IncrementEndPointer( nSize );
	}

	return true;
}