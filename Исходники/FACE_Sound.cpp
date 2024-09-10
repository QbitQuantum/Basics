/*------------------------
	イニシャライズ
  -------------------------*/
STDMETHODIMP CFACE::Sound( LONG DSMODE ){ if ( DSMODE == dwSndMode ) return S_OK;
	// ログに記述
		LogBegin( "Sounds Initializer" );
		LogPut( CONTINUE , IDS_LOG_MODEOUT , DSMODE ); 

	// ハンドルチェック
		CHECK_HWND;
	// グラフィック定数範囲チェック
		CHECK_RANGE( DSMODE , 0 , 1 );

	// 使用しないモード
	if ( DSMODE == SOUNDDISABLE ) SoundRelease( ); 
	else{
		SoundRelease( );	// 全解放
		// DirectSound を作成する。
		if ( FAILED( DirectSoundCreate( NULL , &ObjDS , NULL ) ) )
			DSoundInitFailed;
		// 協調レベルを設定する
		if ( FAILED( ObjDS->SetCooperativeLevel( hWnd , DSSCL_NORMAL ) ) )
			DSoundInitFailed;
		// イベントの作成
		// at Half, at EndPos , FinallyHandler at Half
		for ( int i = 0 ; i < 3 ; i++ ) 
			hEvent[ i ] = CreateEvent( NULL , FALSE , FALSE , NULL );
	}
	dwSndMode = (BYTE)DSMODE;
	LogQuit( );
	return S_OK;
}