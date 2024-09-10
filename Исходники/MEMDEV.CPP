MemoryDevice::~MemoryDevice()
{
	if (m_fOwnsPieces)
	{
	// All pieces are assumed to be BYTE arrays.
		for (int nPiece = 0; nPiece < m_Pieces.count(); nPiece++)
		{
			delete [] (LPBYTE)((MEMORY_DEVICE_PIECE*)m_Pieces.get_element(nPiece))->m_pData;
		}
	// A little heap compaction test.
		_heapmin();
	}
}