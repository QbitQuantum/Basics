/*!
	使ったＡＡをお気に入りＳＱＬにいれる
	@param[in]	pcConts		AAの文字列
	@param[in]	rdLength	バイト数
	@return		HRESULT		終了状態コード
*/
HRESULT AaItemsFavUpload( LPSTR pcConts, UINT rdLength )
{
	LPTSTR	ptBaseName;
	DWORD	dHash;

	ptBaseName = TreeBaseNameGet(  );	//	一覧ベース名取得して

	//	ドロッピンオブジェクトなら無視するので？
	if( !( StrCmp( DROP_OBJ_NAME, ptBaseName ) ) )	return E_ABORT;

	//	そのＡＡのハッシュ値を求めて
	HashData( (LPBYTE)pcConts, rdLength, (LPBYTE)(&(dHash)), 4 );

	//	お気に入りに記録する
	SqlFavUpload( ptBaseName, dHash, pcConts, rdLength );

	return S_OK;
}