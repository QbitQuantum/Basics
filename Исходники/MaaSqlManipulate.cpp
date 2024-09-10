/*!
	ＩＤを指定してデータゲット
	@param[in]	id			検索するＩＤ
	@param[out]	ptFilePath	ファイルパスバッファ・MAX_PATHであること
	@param[out]	ptBaseName	ルート直下のディレクトリ名バッファ・MAX_PATHであること
	@param[in]	ptDispName	タブの表示名・MAX_PATHであること
	@return	UINT	引っ張ったヤツのID番号・ヒットしなかったら０
*/
UINT SqlMultiTabSelect( INT id, LPTSTR ptFilePath, LPTSTR ptBaseName, LPTSTR ptDispName )
{
	CHAR	acQuery[MAX_STRING];
	INT		rslt;
	UINT	index = 0;
	sqlite3_stmt*	statement;


	if( !(gpDataBase) ){	return 0;	}

	StringCchPrintfA( acQuery, MAX_STRING, ("SELECT * FROM MultiTab WHERE id == %d"), id );

	rslt = sqlite3_prepare( gpDataBase, acQuery, -1, &statement, NULL );
	if( SQLITE_OK != rslt ){	SQL_DEBUG( gpDataBase );	return 0;	}

	rslt = sqlite3_step( statement );
	if( SQLITE_ROW == rslt )
	{
		index = sqlite3_column_int( statement , 0 );	//	id
		String_Cch_Copy( ptFilePath, MAX_PATH, (LPCTSTR)sqlite3_column_text16( statement, 1 ) );	//	filepath
		String_Cch_Copy( ptBaseName, MAX_PATH, (LPCTSTR)sqlite3_column_text16( statement, 2 ) );	//	basename
		String_Cch_Copy( ptDispName, MAX_PATH, (LPCTSTR)sqlite3_column_text16( statement, 3 ) );	//	dispname
	}

	sqlite3_finalize( statement );

	return index;
}