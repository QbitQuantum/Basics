TDDSDGenWave::TDDSDGenWave( TDDSD* OWner, const wstring& fname, bool is3D, bool useFX )
{
	FIsStream = false;
	FOwner = OWner;
	FUseFX = useFX;

	//サウンドカードが無いなら、何もしない
	if( ! FOwner->Initialized() )
		return;

	HMMIO hm  =  mmioOpen((LPWSTR)fname.c_str(), NULL, MMIO_READ | MMIO_ALLOCBUF);

	if( hm == 0 ) {
		//PutDebugMessage(fname + 'が、見つかりません');
		return;
	}

	//WAVEに入る
	MMCKINFO mckP;    //親チャンクの情報
	mckP.fccType = MakeFourCC('W','A','V','E');
	if( (mmioDescend(hm, &mckP, NULL, MMIO_FINDRIFF)) != 0 ) {
		mmioClose(hm, 0);
		//PutDebugMessage(fname + 'は、WAVEファイルではありません');
		return;
	}

	//fmtチャンクに入る
	MMCKINFO mckC;    //子チャンクの情報
	mckC.ckid = MakeFourCC('f','m','t',' ');
	if( mmioDescend(hm, &mckC, &mckP, MMIO_FINDCHUNK) != 0 ) {
		mmioClose(hm, 0);
		//PutDebugMessage(fname + 'には、fmtチャンクが有りません');
		return;
	}

	//fmtチャンクを読み取る
	u32 fmtSize  =  mckC.cksize;
	if( mmioRead(hm, (HPSTR)&FWaveFormat, fmtSize) != fmtSize ) {
		mmioClose(hm, 0);
		//PutDebugMessage(fname + 'のfmtチャンクが不正です');
		return;
	}

	//fmtチャンクを抜け、dataチャンクに入る
	mmioAscend(hm, &mckC, 0);
	mckC.ckid = MakeFourCC('d','a','t','a');
	if( mmioDescend(hm, &mckC, &mckP, MMIO_FINDCHUNK) != 0 ) {
		mmioClose(hm, 0);
		//PutDebugMessage(fname + 'には、dataチャンクが有りません');
		return;
	}

	u32 dataSize = mckC.cksize;

	//二次バッファの作成
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	if( is3D )
		dsbd.dwFlags = DSBCAPS_CTRLVOLUME + DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRL3D;
	else
		dsbd.dwFlags = DSBCAPS_CTRLPAN + DSBCAPS_CTRLVOLUME + DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN;

	if( FUseFX )
		dsbd.dwFlags = DSBCAPS_CTRLPAN + DSBCAPS_CTRLVOLUME + DSBCAPS_CTRLFREQUENCY + DSBCAPS_CTRLFX;


	if( FOwner->FStickyFocus )
		dsbd.dwFlags = dsbd.dwFlags | DSBCAPS_STICKYFOCUS;

	dsbd.dwBufferBytes = dataSize;
	dsbd.lpwfxFormat = &FWaveFormat;

	FLength = dataSize;

	IDirectSoundBuffer* dsb;
	FOwner->DSound()->CreateSoundBuffer(&dsbd, &dsb, NULL);
	dsb->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&FSoundBuffer);
	dsb->Release(); 


	//二次バッファのロック
	LPVOID lpBuf1, lpBuf2;
	DWORD dwBuf1, dwBuf2;
	FSoundBuffer->Lock(0,dataSize, &lpBuf1, &dwBuf1, &lpBuf2, &dwBuf2, 0);

	//音データのロード(dataチャンクを読み取る)
	mmioRead(hm, (HPSTR)lpBuf1, dwBuf1);
	if( dwBuf2 != 0 ) {
		mmioRead(hm, (HPSTR)lpBuf2, dwBuf2);
	}

	FSoundBuffer->Unlock(lpBuf1,dwBuf1,lpBuf2,dwBuf2);
	FSoundBuffer->SetFrequency(FWaveFormat.nSamplesPerSec);
	mmioClose(hm, 0);


}