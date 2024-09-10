/*!
	縦書きスクリプトウインドウ作る
	@param[in]	hInst	インスタンスハンドル
	@param[in]	hPrWnd	メインのウインドウハンドル
*/
HWND VertScripterCreate( HINSTANCE hInst, HWND hPrWnd )
{
    LONG	x, y;
    HWND	hDktpWnd;
    UINT	height;
    TCHAR	atBuffer[MAX_STRING];
    RECT	rect, vwRect, dtRect;

    hDktpWnd = GetDesktopWindow(  );
    GetWindowRect( hDktpWnd, &dtRect );

    GetWindowRect( hPrWnd, &rect );
    x = dtRect.right - rect.right;
    if( VT_WIDTH >  x ) {
        rect.right = dtRect.right - VT_WIDTH;
    }

    if( ghVertWnd )
    {
        SetForegroundWindow( ghVertViewWnd );
        SetWindowPos( ghVertWnd, HWND_TOP, rect.right, rect.top, 0, 0, SWP_NOSIZE );
        SetForegroundWindow( ghVertWnd );


        return ghVertWnd;
    }

    gbLeftGo = 0;

    gbSpTrans = 0;

    gbQuickClose = 1;	//	初期状態で直ぐ閉じる

    //	本体ウインドウ
    ghVertWnd = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_TOPMOST, VERTSCRIPT_CLASS,
                                TEXT("縦書き"), WS_POPUP | WS_CAPTION | WS_SYSMENU,
                                rect.right, rect.top, VT_WIDTH, VT_HEIGHT, NULL, NULL, hInst, NULL );

    //	ツールバー
    ghVertToolBar = CreateWindowEx( WS_EX_CLIENTEDGE, TOOLBARCLASSNAME, TEXT("verttoolbar"), WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS, 0, 0, 0, 0, ghVertWnd, (HMENU)IDTB_VLINE_TOOLBAR, hInst, NULL );

    if( 0 == gdToolBarHei )	//	数値未取得なら
    {
        GetWindowRect( ghVertToolBar, &rect );
        gdToolBarHei = rect.bottom - rect.top;
    }

    //	自動ツールチップスタイルを追加
    SendMessage( ghVertToolBar, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_MIXEDBUTTONS );

    SendMessage( ghVertToolBar, TB_SETIMAGELIST, 0, (LPARAM)ghVertImgLst );
    SendMessage( ghVertToolBar, TB_SETBUTTONSIZE, 0, MAKELPARAM(16,16) );

    SendMessage( ghVertToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0 );

    //	ツールチップ文字列を設定・ボタンテキストがツールチップになる
    StringCchCopy( atBuffer, MAX_STRING, TEXT("文字列挿入") );
    gstVttbInfo[0].iString = SendMessage( ghVertToolBar, TB_ADDSTRING, 0, (LPARAM)atBuffer );
    StringCchCopy( atBuffer, MAX_STRING, TEXT("文字列更新") );
    gstVttbInfo[2].iString = SendMessage( ghVertToolBar, TB_ADDSTRING, 0, (LPARAM)atBuffer );
    StringCchCopy( atBuffer, MAX_STRING, TEXT("左から配置") );
    gstVttbInfo[3].iString = SendMessage( ghVertToolBar, TB_ADDSTRING, 0, (LPARAM)atBuffer );
    StringCchCopy( atBuffer, MAX_STRING, TEXT("空白を透過") );
    gstVttbInfo[4].iString = SendMessage( ghVertToolBar, TB_ADDSTRING, 0, (LPARAM)atBuffer );

    SendMessage( ghVertToolBar , TB_ADDBUTTONS, (WPARAM)TB_ITEMS, (LPARAM)&gstVttbInfo );	//	ツールバーにボタンを挿入

    SendMessage( ghVertToolBar , TB_AUTOSIZE, 0, 0 );	//	ボタンのサイズに合わせてツールバーをリサイズ
    InvalidateRect( ghVertToolBar , NULL, TRUE );		//	クライアント全体を再描画する命令

    GetClientRect( ghVertWnd, &rect );

    //	文字間STATIC
    CreateWindowEx( 0, WC_STATIC, TEXT("行間"), WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 2, gdToolBarHei, 45, VT_PARAMHEI, ghVertWnd, (HMENU)IDS_VLINE_INTERVAL, hInst, NULL );
    //	文字間EDIT
    gdVertInterval = 22;
    CreateWindowEx( 0, WC_EDIT, TEXT("22"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 49, gdToolBarHei, 50, VT_PARAMHEI, ghVertWnd, (HMENU)IDE_VLINE_INTERVAL, hInst, NULL );
    //	文字間SPIN
    CreateWindowEx( 0, UPDOWN_CLASS, TEXT("intervalspin"), WS_CHILD | WS_VISIBLE | UDS_AUTOBUDDY, 99, gdToolBarHei, 10, VT_PARAMHEI, ghVertWnd, (HMENU)IDUD_VLINE_INTERVAL, hInst, NULL );

    CreateWindowEx( 0, WC_BUTTON, TEXT("確定したら閉じる"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 120, gdToolBarHei, 180, VT_PARAMHEI, ghVertWnd, (HMENU)IDCB_VLINE_QUICKCLOSE, hInst, NULL );
    CheckDlgButton( ghVertWnd, IDCB_VLINE_QUICKCLOSE, gbQuickClose ? BST_CHECKED : BST_UNCHECKED );

    height = gdToolBarHei + VT_PARAMHEI;

    //文字列入力枠
    ghTextWnd = CreateWindowEx( 0, WC_EDIT, TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
                                0, height, rect.right, rect.bottom - height, ghVertWnd, (HMENU)IDE_VLINE_TEXT, hInst, NULL );
    SetWindowFont( ghTextWnd, ghAaFont, TRUE );

    //	サブクラス
    gpfOrigVertEditProc = SubclassWindow( ghTextWnd, gpfVertEditProc );


    ShowWindow( ghVertWnd, SW_SHOW );
    UpdateWindow( ghVertWnd );


//表示・位置決め半透明フローティングウインドー
    ghVertViewWnd = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_LAYERED, VERTVIEW_CLASS,
                                    TEXT("配置"), WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_VISIBLE, 0, 0, 160, 120, NULL, NULL, hInst, NULL);
    SetLayeredWindowAttributes( ghVertViewWnd, 0, gbAlpha, LWA_ALPHA );
    //	透明度はレイヤボックスの設定を使う

    ZeroMemory( &gstFrmSz, sizeof(POINT) );
    ClientToScreen( ghVertViewWnd, &gstFrmSz );

    //	ウインドウ位置を確定させる
    GetWindowRect( ghViewWnd, &vwRect );	//	編集窓
    gstViewOrigin.x = vwRect.left;	//	ビューウインドウの位置記録
    gstViewOrigin.y = vwRect.top;
    x = (vwRect.left + LINENUM_WID) - gstFrmSz.x;
    y = (vwRect.top  + RULER_AREA)  - gstFrmSz.y;
    TRACE( TEXT("VERT %d x %d"), x, y );
    //	この時点で0dot,0lineの位置にクライヤント左上がアッー！

#ifdef _DEBUG
    SetWindowPos( ghVertViewWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW );
#else
    SetWindowPos( ghVertViewWnd, HWND_TOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW );
#endif
    gstOffset.x = x - vwRect.left;
    gstOffset.y = y - vwRect.top;


    return ghVertWnd;
}