/*！
	ウインドウを作成
	@param[in]	iNowPage	プレビュりたい頁番号
	@param[in]	bForeg		非０なら再プレビューのときにフォアグランドにする・０ならしない・プレビュー開いてないなら何もしない
	@return	HRESULT	終了状態コード
*/
HRESULT PreviewVisibalise( INT iNowPage, BOOLEAN bForeg )
{
	HWND	hWnd;
	TCHAR	atBuffer[MAX_STRING];
//	UINT	iIndex;
	RECT	rect;
	RECT	tbRect;

	HRESULT	hRslt;

	CComPtr<IUnknown>	comPunkIE;	
	CComPtr<IDispatch>	pDispatch;
	CComVariant	vEmpty;
	CComVariant	vUrl( TEXT("about:blank") );

#ifdef REDRAW_ATSCROLL
	LONG	height, offhei, scrtop;
//	CComQIPtr<IHTMLWindow2>		pWindow2;
	CComQIPtr<IHTMLElement>		pElement;
	CComQIPtr<IHTMLElement2>	pElement2;
#endif

	if( ghPrevWnd )	//	已にPreview窓有ったら
	{
	//	SendMessage( ghToolWnd, TB_CHECKBUTTON, IDM_PVW_ALLVW, FALSE );

#pragma message ("全プレ書換時に、スクロールバーの位置覚えておいて、そこまでScrollさせる？")

#ifdef REDRAW_ATSCROLL
		gpWebBrowser2->get_Height( &height );	//	多分コンポーネントの高さ

		gpDocument2->get_body( &pElement );
		pElement.QueryInterface( &pElement2 );
		pElement.Release(  );

		pElement2->get_scrollHeight( &offhei );	//	全体の高さ
		pElement2->get_scrollTop( &scrtop );	//	表示位置のスクロール量
		pElement2.Release(  );

#endif

		//	内容書き換え
		if( 0 > giViewMode ){	PreviewPageWrite(  -1 );	}
		else{	PreviewPageWrite( iNowPage );	}

		gpWebBrowser2->Refresh(  );

#ifdef REDRAW_ATSCROLL
		gpDocument2->get_body( &pElement );
		pElement.QueryInterface( &pElement2 );
		pElement.Release(  );

		pElement2->get_scrollHeight( &offhei );	//	全体の高さ

		pElement2->put_scrollTop(  scrtop );	//	表示位置のスクロール量
		pElement2.Release(  );
#endif

		InvalidateRect( ghPrevWnd, NULL, TRUE );

		if( bForeg )	SetForegroundWindow( ghPrevWnd );

		return S_FALSE;
	}

	//	プレビュー開いてないときに、非フォアグランドなら何もしない
	if( !(bForeg) ){	return  E_ABORT;	}


	InitWindowPos( INIT_LOAD, WDP_PREVIEW, &rect );
	if( 0 >= rect.right || 0 >= rect.bottom )	//	幅高さが０はデータ無し
	{
		hWnd = GetDesktopWindow( );
		GetWindowRect( hWnd, &rect );
		rect.left   = ( rect.right  - PVW_WIDTH ) / 2;
		rect.top    = ( rect.bottom - PVW_HEIGHT ) / 2;
		rect.right  = PVW_WIDTH;
		rect.bottom = PVW_HEIGHT;
		InitWindowPos( INIT_SAVE , WDP_PREVIEW, &rect );	//	起動時保存
	}


	ghPrevWnd = CreateWindowEx( WS_EX_TOOLWINDOW, DOC_PREVIEW_CLASS, TEXT("IEコンポーネントによるプレビュー"),
		WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
		rect.left, rect.top, rect.right, rect.bottom, NULL, NULL, ghInst, NULL );

	//ツールバー作る
	ghToolWnd = CreateWindowEx( 0, TOOLBARCLASSNAME, TEXT("toolbar"),
		WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS | CCS_NODIVIDER,
		0, 0, 0, 0, ghPrevWnd, (HMENU)IDW_PVW_TOOL_BAR, ghInst, NULL );

	//	自動ツールチップスタイルを追加
	SendMessage( ghToolWnd, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_MIXEDBUTTONS );

	SendMessage( ghToolWnd, TB_SETIMAGELIST, 0, (LPARAM)ghPrevwImgLst );

	SendMessage( ghToolWnd, TB_SETBUTTONSIZE, 0, MAKELPARAM(16,16) );

	SendMessage( ghToolWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0 );
	//	ツールチップ文字列を設定・ボタンテキストがツールチップになる
	StringCchCopy( atBuffer, MAX_STRING, TEXT("全プレビュースタイル") );	gstTBInfo[0].iString = SendMessage( ghToolWnd, TB_ADDSTRING, 0, (LPARAM)atBuffer );

	SendMessage( ghToolWnd , TB_ADDBUTTONS, (WPARAM)TB_ITEMS, (LPARAM)&gstTBInfo );	//	ツールバーにボタンを挿入

	SendMessage( ghToolWnd , TB_AUTOSIZE, 0, 0 );	//	ボタンのサイズに合わせてツールバーをリサイズ
	InvalidateRect( ghToolWnd , NULL, TRUE );		//	クライアント全体を再描画する命令

	//	ツールバーサブクラス化が必要

	GetWindowRect( ghToolWnd, &tbRect );
	tbRect.right  -= tbRect.left;
	tbRect.bottom -= tbRect.top;
	tbRect.left = 0;
	tbRect.top  = 0;

	GetClientRect( ghPrevWnd, &rect );
	rect.top     = tbRect.bottom;
	rect.bottom -= tbRect.bottom;

	AtlAxWinInit(  );

	ghIEwnd = CreateWindowEx( 0, ATL_AX_WIN, TEXT("Shell.Explorer.2"),
		WS_CHILD | WS_VISIBLE, rect.left, rect.top, rect.right, rect.bottom,
		ghPrevWnd, (HMENU)IDW_PVW_VIEW_WNDW, ghInst, NULL );

	//	ActiveXコントロールのインターフェースを要求
	if( SUCCEEDED( AtlAxGetControl( ghIEwnd, &comPunkIE ) ) )
	{
		gpWebBrowser2 = comPunkIE;	//	ポインタに格納

		if( gpWebBrowser2 )
		{
			gpWebBrowser2->Navigate2( &vUrl, &vEmpty, &vEmpty, &vEmpty, &vEmpty );

			while( 1 )
			{
				hRslt = gpWebBrowser2->get_Document( &pDispatch );
				if( SUCCEEDED(hRslt) && pDispatch )
				{
					gpDocument2 = pDispatch;
					if( gpDocument2 ){	hRslt = S_OK;	break;	}
				}
				Sleep(100);
			}
		}
		else
		{
			NotifyBalloonExist( TEXT("ＩＥコンポーネントを初期化出来なかったよ・・・"), TEXT("お燐からのお知らせ"), NIIF_ERROR );
			hRslt = E_ACCESSDENIED;
		}
	}

	if( SUCCEEDED(hRslt)  ){	PreviewPageWrite( iNowPage );	}

	UpdateWindow( ghPrevWnd );

	return hRslt;
}