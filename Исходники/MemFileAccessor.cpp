bool CMemFileAccessor::CopyFromClipBroad(UINT ClipFormat)
{
	if(OpenClipboard(NULL))
	{
		HGLOBAL hClip=NULL;

		if( hClip=GetClipboardData(ClipFormat) )
		{
			
			char *pBuff = (char *)GlobalLock(hClip);				
			if(pBuff)
			{				
				SAFE_DELETE_ARRAY(m_Buffer);
				m_BufferSize=GlobalSize(hClip);
				m_DataPtr=0;
				m_WriteSize=0;
				m_Buffer=new char[m_BufferSize];
				memcpy(m_Buffer,pBuff,m_BufferSize);
				GlobalUnlock(hClip);
				CloseClipboard();
				return true;
			}							
		}
		CloseClipboard();		
	}
	return false;
}