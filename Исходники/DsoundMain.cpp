bool Dsoundinit( HWND hwnd )
{	

	// SBArrの初期化
	initSBArr();

	// DirectSound8 の作成
	if (FAILED(DirectSoundCreate8(NULL,&lpDS,NULL)))
	{
		MessageBox(NULL,"DirectSound オブジェクトの作成に失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
		return false;
	}

	// DirectSound の協調レベルを設定
	if (FAILED(lpDS->SetCooperativeLevel(hwnd,DSSCL_PRIORITY)))
	{
		MessageBox(NULL,"DirectSound の協調レベルの設定に失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
		// 閉じる
		SendMessage(hwnd,WM_CLOSE,0,0);
		return false;
	}
	// プライマリ サウンドバッファ作成
	DSBUFFERDESC desc;
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSP,NULL)))
	{
		MessageBox(NULL,"プライマリサウンドバッファの作成に失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
		// 閉じる
		SendMessage(hwnd,WM_CLOSE,0,0);
		return false;
	}
	//ここまでは一回行えばOKの処理

	//SEの数だけセカンダリバッファにデータ読み込み
	//読み込みファイル名をリストから読み込む

	initSBFileList();
	int nCount;

	for(nCount = 0;nCount <= SE_MAX - 1;nCount++){
		// WAVE ファイルの読み込み
//		MessageBox(NULL,SBArr[nCount].cSeFileName,"",MB_OK);

		SBArr[nCount].SB_lpDSB = LoadWave(SBArr[nCount].cSeFileName); //効果音
		if (SBArr[nCount].SB_lpDSB == NULL)
		{
			MessageBox(NULL,"ファイルの読み込みに失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
			// 閉じる
			SendMessage(hwnd,WM_CLOSE,0,0);
			return false;
		}
	}

	return true;
}