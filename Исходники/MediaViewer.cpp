const bool CMediaViewer::InputMedia(CMediaData *pMediaData, const DWORD dwInputIndex)
{
	CBlockLock Lock(&m_DecoderLock);

	/*
	if(dwInputIndex >= GetInputNum())return false;

	CTsPacket *pTsPacket = dynamic_cast<CTsPacket *>(pMediaData);

	// 入力メディアデータは互換性がない
	if(!pTsPacket)return false;
	*/
	CTsPacket *pTsPacket = static_cast<CTsPacket *>(pMediaData);

	// フィルタグラフに入力
	if (m_pSrcFilter
			&& pTsPacket->GetPID() != 0x1FFF
			&& !pTsPacket->IsScrambled()) {
		return m_pSrcFilter->InputMedia(pTsPacket);
	}

	return false;
}