//WAVEファイルをロードする
int WaveLoader::ReadWaveData(WAVEFORMATEX* wfx, void** pdata, QWORD dwFrom, QWORD dwSizeToRead, bool isLoopWave)
{
	static MMCKINFO parent, child;
	static char szBefore[MAX_PATH];
	_ASSERT(m_FileInfo->name);
	if(pdata!=NULL) SAFE_GLOBALFREE(*pdata);

	//if(m_hmmio!=NULL && lstrcmp(m_FileInfo->name, szBefore)!=0){//ファイル名が指定されていたら開きなおす
	//	SAFE_MMIOCLOSE(m_hmmio);
	//}
	if( !isLoaded ){
		lstrcpy(szBefore, m_FileInfo->name);

		if( lstrcmp(m_FileInfo->name, CSL_LOAD_MEMORYIMAGE)==0 ){
//			if(!m_hmmio){//最初の一回しかしない処理（ストリーミング用の処置）
			MMIOINFO mmioinfo;
			zeroMem(&mmioinfo, sizeof(MMIOINFO));
			mmioinfo.pchBuffer = (HPSTR)m_FileInfo->pMemBuffer;
			mmioinfo.fccIOProc = FOURCC_MEM;
			mmioinfo.cchBuffer = m_FileInfo->fsize;

			if(NULL == (m_hmmio = mmioOpen(NULL, &mmioinfo, MMIO_READ|MMIO_ALLOCBUF))){
				return CSL_E_UNEXP;
			}
		}else{
			if(NULL == (m_hmmio = mmioOpen((LPSTR)m_FileInfo->name, NULL, MMIO_READ|MMIO_ALLOCBUF))){
				return CSL_E_UNEXP;
			}
		}
		parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');//waveファイルかどうか調べる
		if(mmioDescend(m_hmmio, &parent, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR){
			SAFE_MMIOCLOSE(m_hmmio);
			return CSL_E_UNEXP;
		}
		child.ckid = mmioFOURCC('f', 'm', 't', ' ');//fmtチャンクへ移動する
		if(mmioDescend(m_hmmio, &child, &parent, MMIO_FINDCHUNK) != MMSYSERR_NOERROR){
			SAFE_MMIOCLOSE(m_hmmio);
			return CSL_E_UNEXP;
		}

		_ASSERT(wfx);
		if(mmioRead(m_hmmio, (HPSTR)wfx, (LONG)child.cksize) != (LONG)child.cksize){//fmtチャンク(WAVEFORMATEX)読み取り
			SAFE_MMIOCLOSE(m_hmmio);
			return CSL_E_UNEXP;
		}
		_ASSERT((wfx->wFormatTag==WAVE_FORMAT_PCM));
		mmioAscend(m_hmmio, &child, 0);//fmtチャンクから出る
		child.ckid = mmioFOURCC('d', 'a', 't', 'a');//dataチャンクに移動
		if(mmioDescend(m_hmmio, &child, &parent, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
			SAFE_MMIOCLOSE(m_hmmio);
			return CSL_E_UNEXP;
		}
		m_dwDataLength = child.cksize;//WAVE領域のサイズ
		m_dwOffsetToWaveData = mmioSeek(m_hmmio, 0, SEEK_CUR);//データまでの位置を保存しておく
	}
	if(pdata){
		if(dwSizeToRead<=0){//ファイル全体を読み込む
			(*pdata) = (LPBYTE)GlobalAlloc(GPTR, m_dwDataLength * sizeof(BYTE));
			_ASSERT(*pdata);

			if(mmioRead(m_hmmio, (HPSTR)*pdata, (LONG)m_dwDataLength) != (LONG)m_dwDataLength){
				GlobalFree(*pdata);
				SAFE_MMIOCLOSE(m_hmmio);
				return CSL_E_UNEXP;
			}
			SAFE_MMIOCLOSE(m_hmmio);	//必要なデータがそろったので､ファイルを閉じる
			m_dwCurrentDecodedPos += dwSizeToRead;
		}else{
			//DWORD dwInnerFinPos = dwFrom + dwSizeToRead;
			////領域サイズ以上だったら収まるように値を補正
			//if(m_dwDataLength < dwInnerFinPos){
			//	dwSizeToRead -= dwInnerFinPos-m_dwDataLength;
			//}

			//開始位置が指定されていれば, データ領域からのオフセットをStartとする.
			//指定されていなければ, それまで進んだカーソル位置から読み込みを開始する
			if(dwFrom>=0) mmioSeek(m_hmmio, (LONG)(m_dwOffsetToWaveData + dwFrom), SEEK_SET);
			
			//要求領域分のメモリ確保
			(*pdata) = (LPBYTE)GlobalAlloc(GPTR, (SIZE_T)(dwSizeToRead * sizeof(BYTE)));
			_ASSERT(*pdata);

			//現在位置からリクエストサイズを読むとオーバーするようなら、ラップアラウンドする。
			DWORD dwNowCursor = mmioSeek(m_hmmio, 0, SEEK_CUR) - m_dwOffsetToWaveData;
			if(m_dwDataLength < (dwNowCursor + dwSizeToRead)){
				if( !isLoopWave ){
					if( dwNowCursor>=m_dwDataLength ){
						fillMem((BYTE*)*pdata, dwSizeToRead, (m_wfx.wBitsPerSample==8) ? 128:0);
						return CSL_E_OUTOFRANGE;
					}
				}

				DWORD dwBeforeWrapAround = m_dwDataLength-dwNowCursor; 
				//とりあえず、最後まで読む
				if(mmioRead(m_hmmio, (HPSTR)*pdata, (LONG)dwBeforeWrapAround) != (LONG)dwBeforeWrapAround){
					GlobalFree(*pdata);
					SAFE_MMIOCLOSE(m_hmmio);
					return CSL_E_UNEXP;
				}
				m_dwCurrentDecodedPos += dwBeforeWrapAround;

				if(isLoopWave){//残った部分を無音で埋めるかどうか
					mmioSeek(m_hmmio, 0, SEEK_SET);
					mmioSeek(m_hmmio, m_dwOffsetToWaveData, SEEK_CUR);	//ポインタをWAVE領域始点に戻す
					//ラップアラウンド分を読む
					if(mmioRead(m_hmmio, (HPSTR)*pdata+dwBeforeWrapAround, (LONG)(dwSizeToRead - dwBeforeWrapAround)) != (LONG)(dwSizeToRead - dwBeforeWrapAround)){
						GlobalFree(*pdata);
						SAFE_MMIOCLOSE(m_hmmio);
						return CSL_E_UNEXP;
					}
					m_dwCurrentDecodedPos =  0;
					m_dwCurrentDecodedPos += dwSizeToRead - dwBeforeWrapAround;
				}else{
					fillMem((BYTE*)*pdata+dwBeforeWrapAround, dwSizeToRead - dwBeforeWrapAround, (m_wfx.wBitsPerSample==8) ? 128:0);
					return CSL_N_FIN;
				}
			}else{ //ラップアラウンドしなかった場合
				if(mmioRead(m_hmmio, (HPSTR)*pdata, (LONG)dwSizeToRead) != (LONG)dwSizeToRead){
					GlobalFree(*pdata);
					SAFE_MMIOCLOSE(m_hmmio);
					return CSL_E_UNEXP;
				}
				m_dwCurrentDecodedPos += dwSizeToRead;
			}//必要なデータはまだあるので、ファイルは閉じない
		}
	}
	return CSL_E_OK;
}