/**
 * ファイルからログイン情報を出力
 */
void Login::Write()
{
	// 実行ファイルのパスからデータファイル名を作成
	CString fileName = theApp.GetAppDirPath() + _T("\\user.dat");

	// ----------------------------------------
	// エンコード処理
	// ----------------------------------------
	FILE* fp = _wfopen(fileName, _T("wb"));
	if (fp == NULL) {
		return;
	}

	// mixi
	WriteItem( fp, GetMixiEmail() );
	WriteItem( fp, GetMixiPassword() );
	CString dummyId;
	WriteItem( fp, dummyId );

	// Twitter
	WriteItem( fp, GetTwitterId() );
	WriteItem( fp, GetTwitterPassword() );

	// Wassr
	WriteItem( fp, GetWassrId() );
	WriteItem( fp, GetWassrPassword() );

	// gooホーム
	WriteItem( fp, GetGooId() );
	WriteItem( fp, GetGoohomeQuoteMailAddress() );

	//--- 以上の9項目は旧バージョンとの互換用データ。
	//--- v1.0.0 以降は下記の汎用データ構造を正する。

	// その他の汎用ID
	CString serializedId = SerializeId();
	WriteItem( fp, serializedId, true );

	fclose(fp);
}