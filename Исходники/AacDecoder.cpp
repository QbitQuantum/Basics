int CAacDecoder::GetSpdifBurstPayload(BYTE *pBuffer, DWORD BufferSize) const
{
	if (pBuffer == NULL || m_pAdtsFrame == NULL)
		return 0;

	if (m_pAdtsFrame->GetRawDataBlockNum() != 0) {
		TRACE(TEXT("Invalid no_raw_data_blocks_in_frame (%d)\r\n"),
			  m_pAdtsFrame->GetRawDataBlockNum());
		return 0;
	}

	const int FrameSize = m_pAdtsFrame->GetFrameLength();
	const int DataBurstSize = (FrameSize + 1) & ~1;
	if (BufferSize < (DWORD)DataBurstSize)
		return 0;

	_swab(pointer_cast<char*>(const_cast<BYTE*>(m_pAdtsFrame->GetData())),
		  pointer_cast<char*>(pBuffer), FrameSize & ~1);
	if (FrameSize & 1) {
		pBuffer[FrameSize - 1] = 0;
		pBuffer[FrameSize] = m_pAdtsFrame->GetAt(FrameSize - 1);
	}

	return DataBurstSize;
}