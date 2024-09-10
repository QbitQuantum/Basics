/*!
	クリップボードのデータをいただく
	@param[in]	pdStyle	矩形かどうかを確認
	@return		確保した文字列・mallocしてるので、函数呼んだ方でfree忘れないように
*/
LPTSTR DocClipboardDataGet( PUINT pdStyle )
{
	LPTSTR	ptString = NULL, ptClipTxt;
	LPSTR	pcStr, pcClipTp;	//	変換用臨時
	DWORD	cbSize;
	UINT	ixSqrFmt, dEnumFmt;
	INT		ixCount, iC;
	HANDLE	hClipData;

	ixSqrFmt = RegisterClipboardFormat( CLIP_SQUARE );

	//	クリップボードの中身をチェキ・どっちにしてもユニコードテキストフラグはある
	if( IsClipboardFormatAvailable( CF_UNICODETEXT ) )
	{
		if( pdStyle )	//	矩形であるか
		{
			if( IsClipboardFormatAvailable( ixSqrFmt ) ){	*pdStyle = D_SQUARE;	}
		}

		OpenClipboard( NULL );	//	クリップボードをオーポンする
		//	開けっ放しだと他のアプリに迷惑なのですぐ閉めるように

		dEnumFmt = 0;	//	初期値は０
		ixCount = CountClipboardFormats(  );
		for( iC = 0; ixCount > iC; iC++ )
		{	//	順番に列挙して、先にヒットしたフォーマットで扱う
			dEnumFmt = EnumClipboardFormats( dEnumFmt );
			if( CF_UNICODETEXT == dEnumFmt || CF_TEXT == dEnumFmt ){	break;	}
		}
		if( 0 == dEnumFmt ){	return NULL;	}
		//	それ以上列挙が無いか、函数失敗なら０になる

		//	クリップボードのデータをゲッツ！
		//	ハンドルのオーナーはクリップボードなので、こちらからは操作しないように
		//	中身の変更などもってのほかである
		hClipData = GetClipboardData( dEnumFmt );

		if( CF_UNICODETEXT == dEnumFmt )
		{
			//	取得データを処理。TEXTなら、ハンドルはグローバルメモリハンドル
			//	新たにコピーされたらハンドルは無効になるので、中身をコピーせよ
			ptClipTxt = (LPTSTR)GlobalLock( hClipData );
			cbSize    = GlobalSize( (HGLOBAL)hClipData );
			//	確保出来るのはバイトサイズ・テキストだと末尾のNULLターミネータ含む

			if( 0 < cbSize )
			{
				ptString = (LPTSTR)malloc( cbSize );
				StringCchCopy( ptString, (cbSize / 2), ptClipTxt );
			}
		}
		else	//	非ユニコードが優先されている場合
		{
			pcClipTp = (LPSTR)GlobalLock( hClipData );
			cbSize   = GlobalSize( (HGLOBAL)hClipData );

			if( 0 < cbSize )
			{
				pcStr = (LPSTR)malloc( cbSize );
				StringCchCopyA( pcStr, cbSize, pcClipTp );

				ptString = SjisDecodeAlloc( pcStr );	//	SJISの内容をユニコードにする
				free( pcStr );
			}
		}


		//	使い終わったら閉じておく
		GlobalUnlock( hClipData );
		CloseClipboard(  );
	}

	return ptString;
}