//----------------------------------------------------------------------------------------------
//	AutomaticChange
//----------------------------------------------------------------------------------------------
VOID CStatusAreaIcon::AutomaticChange( DWORD ProcessID )
{
	//	プロセスのスナップショットを作成する
	HANDLE	ProcessSnapshot	= CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

	//	プロセスのエントリを取得する
	PROCESSENTRY32	ProcessEntry;
	ZeroMemory( &ProcessEntry, sizeof( PROCESSENTRY32 ) );
	ProcessEntry.dwSize = sizeof( PROCESSENTRY32 );
	Process32FirstW( ProcessSnapshot, &ProcessEntry );
	//	全てのプロセスを処理する
	do
	{
		//	フォアグラウンドのアプリケーションを探す
		if( ProcessEntry.th32ProcessID == ProcessID )
		{
			//	モジュール名を切り出す
			WCHAR	ModuleName[MAX_PATH];
			if( wcschr( ProcessEntry.szExeFile, '\\' ) == NULL )
			{
				wcscpy_s( ModuleName, ProcessEntry.szExeFile );
			} else {
				wcscpy_s( ModuleName, &(wcsrchr( ProcessEntry.szExeFile, '\\' )[1]) );
			}

			//	モジュール名と一致するコントローラーの設定を検索する
			for( LONG Index = 1; Index < Setting->SettingCount; Index ++ )
			{
				if(	( _wcsicmp( ModuleName, Setting->SettingName[Index] ) == 0 )
				&&	( Setting->CurrentSettingIndex != Index ) )
				{
					//	コントローラーの設定を変更する
					Setting->Change( Index, TRUE );
					Setting->SaveRegistry();
					Device->Apply();
					break;
				}
			}
			break;
		}
	} while( Process32NextW(ProcessSnapshot, &ProcessEntry ) );

	//	スナップショットを閉じる
	CloseHandle( ProcessSnapshot );
}