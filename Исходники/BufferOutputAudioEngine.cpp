void CBufferOutputAudioEngine::Play()
{
		//BufferTrace("CBufferOutputAudioEngine::Play()....\n");
		if (!m_bFilled && m_mapOutputAudioBuf.size() < (1.0f*BUFFER_PERSEC_AUDIO_NUMBER*BUFFER_OUTPUT_ONMIC_AUDIO_MAX_LIMIT)/1000){
			return ;
		}

		if (!m_bFilled) {
			m_fLastPlayTime = GetTickCount();
			m_iStartPlayCount = 0;
			m_bFilled = true;
		}
		if (m_mapOutputAudioBuf.size() < 1 || (GetTickCount() - m_lastRecvTime) > 1000*10){//10s钟没有收到数据 超时 刷新
			MutexLocker locker(&m_mutex);//播放线程 网络线程 m_mapOutputAudioBuf
			ResetStatus();
			return;
		}

		IsCanCalcRecvRate()?m_fRecvRate = CalcRecevRate():NULL;
		m_fSendRate = CanCalcPlayRate();

		//ErrTrace("CBufferOutputAudioEngine::Play() m_mapOutputAudioBuf.size()=%d,seq=%d,m_fRecvRate=%f,m_fSendRate=%f\n",m_mapOutputAudioBuf.size(),m_iMaxSequenceId - m_iMinSequenceId+1,m_fRecvRate,m_fSendRate);

		unsigned int iLimit = 0;
		DWORD dwCurrTime = GetTickCount();
		while (m_fLastPlayTime < dwCurrTime && ++iLimit<5)
		{
			m_fLastPlayTime += m_fSendRate;
			m_iStartPlayCount++;
			PlayPackets();
			SwitchToThread();
		}
		CheckPacket();
		RefreshStatus();
}