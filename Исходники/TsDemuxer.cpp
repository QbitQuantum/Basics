const bool CTsDemuxer::InputMedia(CMediaData *pMediaData, const DWORD dwInputIndex)
{
	if(dwInputIndex >= GetInputNum())return false;

	CTsPacket *pTsPacket = dynamic_cast<CTsPacket *>(pMediaData);

	// 入力メディアデータは互換性がない
	if(!pTsPacket)return false;

	// 映像PESパケット抽出
	if(pTsPacket->GetPID() == m_wVideoPID){
		m_VideoPesParser.StorePacket(pTsPacket);
		return true;
		}

	// 音声PESパケット抽出
	if(pTsPacket->GetPID() == m_wAudioPID){
		m_AudioPesParser.StorePacket(pTsPacket);
		return true;
		}

	return true;
}