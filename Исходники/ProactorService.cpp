void ProactorService::SendInternal(char* pBuffer, int bufferSize)
{			
	ACE_Message_Block* pBlock = NULL;

	ACE_NEW_NORETURN(pBlock, ACE_Message_Block(bufferSize));

	pBlock->copy((const char*)pBuffer, bufferSize);

	if(NULL == pBlock->cont())
	{
		m_AsyncWriter.write(*pBlock, pBlock->length());
	}
	else
	{
		m_AsyncWriter.writev(*pBlock, pBlock->total_length());
	}	
}