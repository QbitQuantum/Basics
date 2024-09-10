/*!
	指定ドット位置が含まれている、スペースか非スペースの文字の始点終点ドット数確保
	@param[in]	dDot	指定ドット・これの左の文字で判断
	@param[in]	rdLine	行数
	@param[out]	pLeft	始点ドット・行頭かも
	@param[out]	pRight	終点ドット・行末かも
	@param[out]	pStCnt	開始地点の文字数・NULLでも可
	@param[out]	pCount	間の文字数・NULLでも可
	@param[out]	pIsSp	該当はスペースであるか？
	@return		該当範囲のドット数
*/
INT DocLineStateCheckWithDot( INT dDot, INT rdLine, PINT pLeft, PINT pRight, PINT pStCnt, PINT pCount, PBOOLEAN pIsSp )
{
	UINT_PTR	iCount;
	INT		bgnDot, endDot;
	INT		iBgnCnt, iRngCnt;
	TCHAR	ch, chb;
	UINT	dMozis;
	INT		bSpace;
	LETR_ITR	itMozi, itHead, itTail, itTemp;

	LINE_ITR	itLine;

	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, rdLine );

	if( !(pLeft) || !(pRight) || !(pIsSp) ){	return 0;	}

	itMozi = itLine->vcLine.begin( );
	iCount = itLine->vcLine.size( );	//	この行の文字数確認

	//	中身が無いならエラー
	if( 0 >= iCount ){	*pIsSp =  FALSE;	*pLeft =  0;	*pRight = 0;	return 0;	}

	dMozis = DocLetterPosGetAdjust( &dDot , rdLine, 0 );	//	今の文字位置を確認

	if( 1 <= dMozis ){	itMozi += (dMozis-1);	}	//	キャレットの位置の左文字で判定
	//	最初から先頭ならなにもしなくておｋ
	ch = itMozi->cchMozi;
	bSpace = iswspace( ch );


	//	その場所から頭方向に辿って、途切れ目を探す
	itHead = itLine->vcLine.begin( );

	for( ; itHead != itMozi; itMozi-- )
	{
		chb = itMozi->cchMozi;
		if( iswspace( chb ) != bSpace ){	itMozi++;	break;	}
	}
	//	先頭までイッちゃった場合・これが抜けてた
	if( itHead == itMozi )
	{
		chb = itMozi->cchMozi;
		if( iswspace( chb ) != bSpace ){	itMozi++;	}
	}
	//	基準と異なる文字にヒットしたか、先頭位置である

	//	先頭から、ヒット位置まで辿ってドット数と文字数確認
	bgnDot = 0;
	iBgnCnt = 0;
	for( itTemp = itHead; itTemp != itMozi; itTemp++ )
	{
		bgnDot += itTemp->rdWidth;	//	文字幅増やして
		iBgnCnt++;	//	文字数も増やす
	}//もし最初から先頭なら両方０のまま

	itTail = itLine->vcLine.end( );

	//	その場所から、同じグループの所まで確認
	endDot = bgnDot;
	iRngCnt = 0;
	for( ; itTemp != itTail; itTemp++ )
	{
		chb = itTemp->cchMozi;	//	同じタイプである間加算続ける
		if( iswspace( chb ) != bSpace ){	break;	}

		endDot += itTemp->rdWidth;
		iRngCnt++;
	}

	*pLeft  = bgnDot;
	*pRight = endDot;
	*pIsSp  = bSpace ? TRUE : FALSE;

	if( pCount )	*pCount = iRngCnt;
	if( pStCnt )	*pStCnt = iBgnCnt;

	return (endDot - bgnDot);
}