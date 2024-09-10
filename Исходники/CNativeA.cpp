/* 半角→全角 */
void CNativeA::ToZenkaku(
		int bHiragana,		/* 1== ひらがな 0==カタカナ //2==英数専用 2001/07/30 Misaka 追加 */
		int bHanKataOnly	/* 1== 半角カタカナにのみ作用する*/
)
{
	unsigned char*			pBuf = (unsigned char*)GetStringPtr();
	int						nBufLen = GetStringLength();
	int						i;
	int						nCharChars;
//	unsigned char			uc;
	unsigned short			usSrc;
	unsigned short			usDes;
	unsigned char*			pBufDes;
	int						nBufDesLen;
	static unsigned char*	pszHanKataSet = (unsigned char*)"｡｢｣､･ｦｧｨｩｪｫｬｭｮｯｰｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝﾞﾟ";
	static unsigned char*	pszDakuSet = (unsigned char*)"ｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾊﾋﾌﾍﾎ";
	static unsigned char*	pszYouSet = (unsigned char*)"ﾊﾋﾌﾍﾎ";
	BOOL					bHenkanOK;

	pBufDes = new unsigned char[nBufLen * 2 + 1];
	if( NULL ==	pBufDes ){
		return;
	}
	nBufDesLen = 0;
	for( i = 0; i < nBufLen; ++i ){
		// 2005-09-02 D.S.Koba GetSizeOfChar
		nCharChars = CShiftJis::GetSizeOfChar( (const char *)pBuf, nBufLen, i );
		if( nCharChars == 1){
			bHenkanOK = FALSE;
			if( bHanKataOnly ){	/* 1== 半角カタカナにのみ作用する */
				if( NULL != strchr( (const char *)pszHanKataSet, pBuf[i] ) ){
					bHenkanOK = TRUE;
				}
			}else{
				//! 英数変換用に新たな条件を付加 2001/07/30 Misaka
				if( ( (unsigned char)0x20 <= pBuf[i] && pBuf[i] <= (unsigned char)0x7E ) ||
					( bHiragana != 2 && (unsigned char)0xA1 <= pBuf[i] && pBuf[i] <= (unsigned char)0xDF )
				){
					bHenkanOK = TRUE;
				}
			}
			if( bHenkanOK ){
				usSrc = pBuf[i];
				if( !bHiragana &&
					pBuf[i]		== (unsigned char)'ｳ' &&
					pBuf[i + 1] == (unsigned char)'ﾞ' &&
					bHiragana != 2
				){
					usDes = (unsigned short)0x8394; /* ヴ */
					nCharChars = 2;
				}else {
					usDes = (unsigned short)_mbbtombc( usSrc );
					/* 濁音 */
					if( bHiragana != 2 && pBuf[i + 1] == (unsigned char)'ﾞ' && NULL != strchr( (const char *)pszDakuSet, pBuf[i] ) ){
						usDes++;
						nCharChars = 2;
					}
					/* 拗音 */
					//! 英数変換用に新たな条件を付加 2001/07/30 Misaka
					//! bHiragana != 2 //英数変換フラグがオンではない場合
					if( bHiragana != 2 && pBuf[i + 1] == (unsigned char)'ﾟ' && NULL != strchr( (const char *)pszYouSet, pBuf[i] ) ){
						usDes += 2;
						nCharChars = 2;
					}
				}

				if( bHiragana == 1 ){
					/* ひらがなに変換可能なカタカナならば、ひらがなに変換する */
					if( (unsigned short)0x8340 <= usDes && usDes <= (unsigned short)0x837e ){	/* ァ〜ミ */
						usDes-= (unsigned short)0x00a1;
					}else
					if( (unsigned short)0x8380 <= usDes && usDes <= (unsigned short)0x8393 ){	/* ム〜ン */
						usDes-= (unsigned short)0x00a2;
					}
				}
				pBufDes[nBufDesLen]		= ( usDes & 0xff00 ) >>  8;
				pBufDes[nBufDesLen + 1] = ( usDes & 0x00ff );
				nBufDesLen += 2;
			}else{
				memcpy( &pBufDes[nBufDesLen], &pBuf[i], nCharChars );
				nBufDesLen += nCharChars;

			}
		}else