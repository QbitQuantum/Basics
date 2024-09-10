void CTcpPullClient::DoFetch(BYTE* pBuffer, int iLength)
{
	int iIndex	= 0;
	int iRemain	= iLength;

	while(iRemain > 0)
	{
		CBufferPtr* pItem = m_pullBuffers->front();
		int iItemSize = (int)pItem->Size();
		int iCopySize = min(iItemSize, iRemain);

		memcpy(pBuffer + iIndex, pItem->Ptr(), iCopySize);

		if(iItemSize > iRemain)
		{
			int iLeft = iItemSize - iCopySize;
			memcpy(pItem->Ptr(), pItem->Ptr() + iCopySize, iLeft);
			pItem->Realloc(iLeft);
		}
		else
		{
			m_pullBuffers->pop_front();
			delete pItem;
		}

		iRemain	-= iCopySize;
		iIndex	+= iCopySize;
	}
}