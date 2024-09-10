/* 全行データを返す
	改行コードは、CRLFに統一される。
	@retval 全行データ。freeで解放しなければならない。
	@note   Debug版のテストにのみ使用している。
*/
wchar_t* CDocReader::GetAllData(int* pnDataLen)
{
	int			nDataLen;
	int			nLineLen;
	const CDocLine* 	pDocLine;

	pDocLine = m_pcDocLineMgr->GetDocLineTop();
	nDataLen = 0;
	while( NULL != pDocLine ){
		//	Oct. 7, 2002 YAZAKI
		nDataLen += pDocLine->GetLengthWithoutEOL() + 2;	//	\r\nを追加して返すため+2する。
		pDocLine = pDocLine->GetNextLine();
	}

	wchar_t* pData;
	pData = (wchar_t*)malloc( (nDataLen + 1) * sizeof(wchar_t) );
	if( NULL == pData ){
		TopErrorMessage( NULL, LS(STR_ERR_DLGDOCLM6), nDataLen + 1 );
		return NULL;
	}
	pDocLine = m_pcDocLineMgr->GetDocLineTop();

	nDataLen = 0;
	while( NULL != pDocLine ){
		//	Oct. 7, 2002 YAZAKI
		nLineLen = pDocLine->GetLengthWithoutEOL();
		if( 0 < nLineLen ){
			wmemcpy( &pData[nDataLen], pDocLine->GetPtr(), nLineLen );
			nDataLen += nLineLen;
		}
		pData[nDataLen++] = L'\r';
		pData[nDataLen++] = L'\n';
		pDocLine = pDocLine->GetNextLine();
	}
	pData[nDataLen] = L'\0';
	*pnDataLen = nDataLen;
	return pData;
}