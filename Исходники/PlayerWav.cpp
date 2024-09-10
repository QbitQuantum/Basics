DWORD CPlayer::WavPlayerThread()
{
	BOOL fFlush = FALSE;
	if (m_pwfxSrc->wFormatTag == WAVE_FORMAT_PCM) {
		// PCM
		DWORD cbInBuf, cbRead;
		while (TRUE) {
			// 停止フラグのチェック
			if (m_fStop)
				return RET_STOP;

			if (!m_pOutHdr)
				m_pOutHdr = m_Output.GetBuffer();

			{
				// Critical Sectionのセット
				CAutoLock lock(&m_csecThread);
				if (m_fSeek) {
					if (m_Status == MAP_STATUS_PLAY)
						m_fPlay = TRUE;

					m_Reverb.Reset();
					m_Echo.Reset();
					m_BassBoost.Reset();
					m_3DChorus.Reset();
					m_Output.Reset();
					m_fSeek = FALSE;
					m_pOutHdr = NULL;
					continue;
				}

				// 読み込み
				cbRead = min(m_dwDataSize - m_dwCurrentSize, m_cbOutBuf);
				if (!m_Reader.Read((LPBYTE)m_pOutHdr->lpData, cbRead, &cbInBuf) || !cbInBuf) {
					if (GetLastError() != ERROR_SUCCESS)
						return RET_ERROR;
					fFlush = TRUE;
				}

				Preamp((LPBYTE)m_pOutHdr->lpData, cbInBuf);

				m_dwCurrentSize += cbInBuf;
			}
			if (fFlush)
				return RET_EOF;

			OutputBuffer(m_pOutHdr, cbInBuf);
			m_cbOutBufLeft = 0;
			m_pOutHdr = NULL;

			if (m_dwCurrentSize >= m_dwDataSize)
				return RET_EOF;
			if (m_fSuppress)
				return RET_EOF;
		}
	}
	else {
		// PCM 以外
		// デコード開始
		BYTE bRead[WAV_FILE_BUFF_LEN];
		DWORD cbInBuf, cbRead;
		while (TRUE) {
			// 停止フラグのチェック
			if (m_fStop)
				return RET_STOP;

			// 出力バッファの確保
			if (m_pOutHdr) {
				OutputBuffer(m_pOutHdr, m_cbOutBuf - m_cbOutBufLeft);
				m_cbOutBufLeft = 0;
				m_pOutHdr = NULL;
			}
			if (m_fSuppress)
				return RET_EOF;
			m_pOutHdr = m_Output.GetBuffer();
			m_cbOutBufLeft = m_cbOutBuf;

			{
				// Critical Sectionのセット
				CAutoLock lock(&m_csecThread);
				if (m_fSeek) {
					if (m_Status == MAP_STATUS_PLAY)
						m_fPlay = TRUE;

					m_Reverb.Reset();
					m_Echo.Reset();
					m_BassBoost.Reset();
					m_Output.Reset();
					m_fSeek = FALSE;
					m_pOutHdr = NULL;
					acmStreamReset(m_hAcm, 0);
					continue;
				}

				acmStreamSize(m_hAcm, m_cbOutBufLeft, &cbRead, 
								ACM_STREAMSIZEF_DESTINATION);

				// 読み込み
				cbRead = min(m_dwDataSize - m_dwCurrentSize, cbRead);
				cbRead = min(WAV_FILE_BUFF_LEN, cbRead);
				if (!m_Reader.Read(bRead, cbRead, &cbInBuf) || !cbInBuf) {
					if (GetLastError() != ERROR_SUCCESS)
						return RET_ERROR;

					fFlush = TRUE;
				}
				m_dwCurrentSize += cbInBuf;
			}
			if (fFlush)
				return RET_EOF;

			// ヘッダの確保
			ACMSTREAMHEADER ash;
			memset(&ash, 0, sizeof(ash));
			ash.cbStruct = sizeof(ash); //構造体のサイズ
			ash.pbSrc = bRead;
			ash.cbSrcLength = cbInBuf;
			ash.pbDst = (LPBYTE)m_pOutHdr->lpData + (m_cbOutBuf - m_cbOutBufLeft);
			ash.cbDstLength = m_cbOutBufLeft;
			if (acmStreamPrepareHeader(m_hAcm, &ash, 0))
				break;

			// 変換
			if (acmStreamConvert(m_hAcm, &ash, 0))
				break;

			Preamp((LPBYTE)m_pOutHdr->lpData + (m_cbOutBuf - m_cbOutBufLeft), ash.cbDstLengthUsed);
			m_cbOutBufLeft -= ash.cbDstLengthUsed;

			// 後処理
			if (acmStreamUnprepareHeader(m_hAcm, &ash, 0))
				break;

			if (m_dwCurrentSize >= m_dwDataSize)
				return RET_EOF;
		}

		return RET_ERROR;
	}
}