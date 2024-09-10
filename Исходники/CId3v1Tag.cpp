/*
	Link()
*/
BOOL CId3v1Tag::Link(const char* lpcszFileName)
{
	BOOL bRet = FALSE;
	
	Unlink();

	strcpyn(m_szFileName,lpcszFileName,sizeof(m_szFileName));
	{
		CBinFileEx file;

		if(file.OpenExistingReadOnly(m_szFileName))
		{
			if(file.SeekEx((LONGLONG)sizeof(m_ID3v1) * -1,FILE_END)!=FILE_EEOF)
				if(file.Read(m_ID3v1,sizeof(m_ID3v1))!=FILE_EOF)
				{
					SetTagsFromTag();
					bRet = TRUE;
				}
			
			file.Close();
		}
	}

	return(bRet);
}