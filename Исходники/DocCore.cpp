/*!
	ページ全体を確保する・freeは呼んだ方でやる
	@param[in]	bStyle	１ユニコードかシフトJIS
	@param[out]	*pText	確保した領域を返す・ワイド文字かマルチ文字になる・NULLだと必要バイト数を返すのみ
	@return				確保したバイト数・NULLターミネータも含む
*/
INT DocPageTextAllGetAlloc( UINT bStyle, LPVOID *pText )
{
	//	SJISの場合は、ユニコード文字は&#dddd;で確保される

	UINT_PTR	iLines, i, iLetters, j;
	UINT_PTR	cchSize;
	INT_PTR		iSize;

	LPTSTR		ptData;
	LPSTR		pcStr;

	string	srString;	//	ユニコード・シフトJISで確保
	wstring	wsString;

	LINE_ITR	itLine;


	srString.clear( );
	wsString.clear( );

	if( gitFileIt->vcCont.at( gixFocusPage ).ptRawData )	//	生データ状態なら
	{
		ptData = (*gitFileIt).vcCont.at( gixFocusPage ).ptRawData;
		StringCchLength( ptData, STRSAFE_MAX_CCH, &cchSize );

		if( bStyle & D_UNI )	//	ユニコードである
		{
			iSize = (cchSize+1) * sizeof(TCHAR);	//	NULLターミネータ分足す

			if( pText )
			{
				*pText = (LPTSTR)malloc( iSize );
				ZeroMemory( *pText, iSize );
				StringCchCopy( (LPTSTR)(*pText), cchSize, ptData );
			}
		}
		else
		{
			pcStr = SjisEncodeAlloc( ptData );
			if( pcStr )
			{
				StringCchLengthA( pcStr, STRSAFE_MAX_CCH, &cchSize );
				iSize = cchSize + 1;	//	NULLターミネータ分足す

				if( pText ){	*pText =  pcStr;	}
				else{	FREE( pcStr );	}
			}
		}
	}
	else
	{
		//	ページ全体の行数
		iLines = DocNowFilePageLineCount( );

		itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();

		for( i = 0; iLines > i; i++, itLine++ )
		{
			//	各行の文字数
			iLetters = itLine->vcLine.size( );

			if( bStyle & D_UNI )
			{
				for( j = 0; iLetters > j; j++ )
				{
					wsString += itLine->vcLine.at( j ).cchMozi;
				}

				if( iLines > (i+1) )	wsString += wstring( CH_CRLFW );
			}
			else
			{
				for( j = 0; iLetters > j; j++ )
				{
					srString +=  string( itLine->vcLine.at( j ).acSjis );
				}

				if( iLines > (i+1) )	srString +=  string( CH_CRLFA );
			}
		}

		if( bStyle & D_UNI )	//	ユニコードである
		{
			cchSize = wsString.size(  ) + 1;	//	NULLターミネータ分足す
			iSize = cchSize * sizeof(TCHAR);	//	ユニコードなのでバイト数は２倍である

			if( pText )
			{
				*pText = (LPTSTR)malloc( iSize );
				ZeroMemory( *pText, iSize );
				StringCchCopy( (LPTSTR)(*pText), cchSize, wsString.c_str( ) );
			}
		}
		else
		{
			iSize = srString.size( ) + 1;	//	NULLターミネータ分足す

			if( pText )
			{
				*pText = (LPSTR)malloc( iSize );
				ZeroMemory( *pText, iSize );
				StringCchCopyA( (LPSTR)(*pText), iSize, srString.c_str( ) );
			}
		}
	}

	return iSize;
}