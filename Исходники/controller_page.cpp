//----------------------------------------------------------------------------------------------
//	ApplySetting
//----------------------------------------------------------------------------------------------
VOID CControllerPage::ApplySetting()
{
	//	変数宣言
	BOOL	Different	= FALSE;

	//	コンボ ボックスの内容が異なるかチェックする
	HWND	ComboBox		= GetDlgItem( Wnd, IDC_SETTING );
	LONG	ItemCount		= (LONG)SendMessage( ComboBox, CB_GETCOUNT, 0, 0 );
	if( Setting->ModifiedFlag == TRUE )
	{
		ItemCount --;
	}
	if( ItemCount == Setting->SettingCount )
	{
		//	アイテムの文字列をチェックする
		for( LONG Index = 0; Index < Setting->SettingCount; Index ++ )
		{
			//	コンボ ボックスの文字列を取得する
			WCHAR	Text[MAX_PATH]	= { '\n' };
			if( Setting->ModifiedFlag == TRUE )
			{
				SendMessage( ComboBox, CB_GETLBTEXT, Index + 1, (LPARAM)Text );
			} else {
				SendMessage( ComboBox, CB_GETLBTEXT, Index, (LPARAM)Text );
			}
			if( wcscmp( Setting->SettingName[Index], Text ) != 0 )
			{
				Different	= TRUE;
				break;
			}
		}
	} else {
		Different	= TRUE;
	}

	//	コンボ ボックスの内容を設定する
	if( Different == TRUE )
	{
		//	コンボ ボックスの内容をリセットする
		SendMessage( ComboBox, CB_RESETCONTENT, 0, 0 );

		//	設定名称をコンボ ボックスに挿入する
		for( LONG Index = 0; Index < Setting->SettingCount; Index ++ )
		{
			SendMessage(
				 ComboBox
				,CB_INSERTSTRING
				,Index
				,(LPARAM)Setting->SettingName[Index] );
		}

		//	設定が変更済みなら一番上に「〜 (変更済み)」を挿入する
		if( Setting->ModifiedFlag == TRUE )
		{
			//	設定名称を取得する
			WCHAR	SettingName[MAX_PATH * 2];
			wcscpy_s( SettingName, Setting->SettingName[Setting->CurrentSettingIndex] );

			//	リソースから「(変更済み)」を取得し、設定名称に付加する
			WCHAR	Modified[MAX_PATH];
			LoadString( Instance, IDS_MODIFIED, Modified, MAX_PATH );
			wcscat_s( SettingName, Modified );

			//	変更済みの設定名称をコンボ ボックスの一番上に挿入する
			SendMessage( ComboBox, CB_INSERTSTRING, 0, (LPARAM)SettingName );
		}
	}

	//	コンボ ボックスの順番を設定する
	if( Setting->ModifiedFlag == FALSE )
	{
		SetComboBoxIndex( IDC_SETTING, (UCHAR)Setting->CurrentSettingIndex );
	} else {
		SetComboBoxIndex( IDC_SETTING, 0 );
	}
	//	削除ボタンの有効、無効を設定する
	if( Setting->ModifiedFlag == FALSE && Setting->CurrentSettingIndex > 0 )
	{
		EnableControl( IDC_SETTING_DELETE, TRUE );
	} else {
		EnableControl( IDC_SETTING_DELETE, FALSE );
	}
}