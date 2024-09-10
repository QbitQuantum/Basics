int CSound::LoadInternal(const char* szFileName, DSBUFFERDESC* pDsbdesc, void* pData, unsigned long dwDataSize){

	CSoundLoader* pLoader;
	char errmsg[512];
	if(CS_E_OK!=this->GetLoaderInterface(&pLoader, szFileName, pData, dwDataSize)){
		wsprintf(errmsg, "Sound::%sの読み取りインターフェイス取得に失敗.\nファイルが存在するかもしくは対応形式か確認して下さい.", szFileName);
		::MessageBox(NULL, errmsg, "", MB_ICONEXCLAMATION|MB_OK|MB_TOPMOST);
		//FatalAppExit(0, errmsg);
		return CS_E_NOTFOUND;
	}
	if(CSL_E_OK != pLoader->QueryLoadFile(szFileName, pData, dwDataSize)){
		wsprintf(errmsg, "Sound::%sの読み取りに失敗.", szFileName);
		::MessageBox(NULL, errmsg, "", MB_ICONEXCLAMATION|MB_OK|MB_TOPMOST);
		//FatalAppExit(0, errmsg);
		return CS_E_UNEXP;
	}

	//初期化
	this->AddRef();
	this->UnInitialize();

	m_Loader = pLoader;

	if(!m_pPrimaryBuffer){		//プライマリバッファを取得する
		if(CS_E_OK!=GetPrimaryBuffer(&m_pPrimaryBuffer, DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER)) return CS_E_NULL_PRIMARY;
	}

	DSBUFFERDESC dsbdesc;
	zeroMem(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//全体の長さとWFXの取得
	DWORD dwDataLength = m_Loader->GetDecodedLength();
	m_Loader->GetWaveFormatEx(&m_wfx);
	if(dwDataLength >= CS_LIMITLOADONMEMORY){//展開したときのサイズが1MB以上だったらストリーミング再生]
		//スレッド処理
		this->CloseStreamThread();
		m_hThreadMessageDispatchEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThread = CreateThread(NULL, 0, this->StreamThread, (void*)this, CREATE_SUSPENDED, &m_dwThreadId);		//スレッド生成
		// スレッド優先を変更
		SetThreadPriority( m_hThread, THREAD_PRIORITY_NORMAL ); 
		// スレッド開始
		ResumeThread( m_hThread );
		WaitForSingleObject(m_hThreadMessageDispatchEvent, INFINITE);// スレッドメッセージキューが作成されるのを待つ

		m_isStreamFile = TRUE;

		//セカンダリバッファ
		{
			SAFE_RELEASE(m_pSecondaryBuffer);
			dsbdesc.dwFlags =	DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_CTRLPOSITIONNOTIFY|
								DSBCAPS_GLOBALFOCUS|DSBCAPS_CTRLPAN|DSBCAPS_CTRLVOLUME|
								DSBCAPS_CTRLFREQUENCY|DSBCAPS_LOCSOFTWARE;

			if(pDsbdesc){
				dsbdesc.dwFlags = pDsbdesc->dwFlags;
				dsbdesc.guid3DAlgorithm = dsbdesc.guid3DAlgorithm;
			}
			dsbdesc.lpwfxFormat = &m_wfx;
			DWORD dwSize = m_wfx.nAvgBytesPerSec * m_dwBufferLengthSec / m_dwNotificationNum;
			dwSize -= dwSize % m_wfx.nBlockAlign;
			dsbdesc.dwBufferBytes = dwSize * m_dwNotificationNum;
			if(!CreateBuffer(&m_pSecondaryBuffer, &dsbdesc, NULL))	return CS_E_NOCANDO;

			m_dwOneSplittedBufferSize = dwSize;//区切られたバッファの１つのサイズ（バッファ全体はこれ*m_dwNotificationNum
		}

		//通知インターフェイス
#if !ENABLE_SOUND_POLLING
		{
			SAFE_RELEASE(m_pSoundNotify);
			if(FAILED(m_pSecondaryBuffer->QueryInterface(IID_IDirectSoundNotify, (void**)&m_pSoundNotify))){
				return CS_E_NOCANDO;
			}

			SAFE_GLOBALFREE(m_pDsbnotify);
			if(!(m_pDsbnotify = (DSBPOSITIONNOTIFY*)GlobalAlloc(GPTR, m_dwNotificationNum * sizeof(DSBPOSITIONNOTIFY)))){
				return CS_E_UNEXP;
			}

			m_pNotifyHandle = CreateEvent(NULL, FALSE, FALSE, NULL);	//通知ハンドルの作成
			for(DWORD i=0; i<m_dwNotificationNum; i++){
				//OutputDebugStringFormatted("[%2lu]:%lu\n", i, (m_dwOneSplittedBufferSize*i) + 1);
				m_pDsbnotify[i].dwOffset     = (m_dwOneSplittedBufferSize*i) + 1;// バッファを分割する。通知ポイントは、バッファの区切れ目から1バイト先。こうすることで、スペックの低いマシンでも249ms以内に次のバッファ区間を埋めればよいことになる。
				m_pDsbnotify[i].hEventNotify = m_pNotifyHandle;
			}
			if(FAILED(m_pSoundNotify->SetNotificationPositions(m_dwNotificationNum, m_pDsbnotify))){
				SAFE_GLOBALFREE(m_pDsbnotify);
				SAFE_RELEASE(m_pSoundNotify);
				SAFE_CLOSEHANDLE(m_pNotifyHandle);
				return CS_E_NOCANDO;
			}
		}
#endif
	}else{
		m_isStreamFile = FALSE;

		void* pdata = NULL;
		if(CSL_E_OK != m_Loader->GetDecodedData(&pdata, 0, 0, FALSE)){
		}

		dsbdesc.dwFlags =	DSBCAPS_CTRLPAN|DSBCAPS_CTRLVOLUME|
							DSBCAPS_CTRLFREQUENCY|
							DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_CTRLPOSITIONNOTIFY|
							DSBCAPS_GLOBALFOCUS;
		if(pDsbdesc){
			dsbdesc.dwFlags = pDsbdesc->dwFlags;
			dsbdesc.guid3DAlgorithm = dsbdesc.guid3DAlgorithm;
		}
		dsbdesc.dwBufferBytes = dwDataLength;
		dsbdesc.lpwfxFormat = &m_wfx;

		SAFE_RELEASE(m_pSecondaryBuffer);
		if(!CreateBuffer(&m_pSecondaryBuffer, &dsbdesc, NULL)) return CS_E_NOCANDO;		//セカンダリバッファの作成
		if(!WriteDataToBuffer(&m_pSecondaryBuffer, pdata, 0, dwDataLength))	return CS_E_NOCANDO;		//データをバッファに書き込む
		
		SAFE_GLOBALFREE(pdata);
	}
	SAFE_RELEASE(m_pPrimaryBuffer);
	return CS_E_OK;
}