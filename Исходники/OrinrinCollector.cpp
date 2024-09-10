/*!
	クリップボードに変更があった場合の処理・自分からの変更に反応しないようにせにゃ
	@param[in]	hWnd	ウインドウハンドル・使わないか
	@return	HRESULT	終了状態コード
*/
HRESULT ClipStealDoing( HWND hWnd )
{
	LPTSTR		ptTexts;
	LPSTR		pcStrs;
	CHAR		acBuffer[MAX_STRING];
	TCHAR		atMsg[MAX_STRING];

	UINT_PTR	cbSize, cbSplSz;
	DWORD		wrote;

	HANDLE	hFile;

	SYSTEMTIME	stTime;


	//	保存するファイル指定が無いならナニもしない
	if( NULL == gatClipFile[0] ){	return E_NOTIMPL;	}

	//	クリップスティール機能有効？
	if( !(gbClipSteal) ){	return  S_FALSE;	}


	ptTexts = ClipboardDataGet( NULL );
	if( !(ptTexts) ){	return E_ACCESSDENIED;	}
	//	クリップされたのが文字列ではなかったら直ぐ終わる

	//	SJIS型に変換
	pcStrs = SjisEncodeAlloc( ptTexts );
	StringCchLengthA( pcStrs, STRSAFE_MAX_CCH, &cbSize );

	//	ゲットしたコピペ文字列の保存処理
	hFile = CreateFile( gatClipFile, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( INVALID_HANDLE_VALUE != hFile )
	{
		SetFilePointer( hFile, 0, NULL, FILE_END );

		if( gIsAST )
		{
			GetLocalTime( &stTime );
			StringCchPrintfA( acBuffer, MAX_STRING, ("[AA][%04u/%02u/%02u %02u:%02u:%02u]\r\n"),
				stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond );
			StringCchLengthA( acBuffer, MAX_STRING, &cbSplSz );
			WriteFile( hFile, acBuffer, cbSplSz, &wrote, NULL );
		}

		WriteFile( hFile, pcStrs, cbSize, &wrote, NULL );

		if( gIsAST ){	StringCchCopyA( acBuffer, MAX_STRING, ("\r\n") );	}
		else{	StringCchCopyA( acBuffer, MAX_STRING, ("\r\n[SPLIT]\r\n") );	}
		StringCchLengthA( acBuffer, MAX_STRING, &cbSplSz );
		WriteFile( hFile, acBuffer, cbSplSz, &wrote, NULL );

		SetEndOfFile( hFile );
		CloseHandle( hFile );
	}

	FREE( ptTexts );
	FREE( pcStrs );

	//	保存したメッセージが必要
	if( gGetMsgOn )
	{
		StringCchPrintf( atMsg, MAX_STRING, TEXT("%u Byte 取得"), cbSize );
		TaskTrayIconBalloon( hWnd, TEXT("コピーされた文字列を保存したよ。"), atMsg, 1 );
	}

	return S_OK;
}