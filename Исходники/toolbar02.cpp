HWND MyCreateToolbar(HWND hWnd)
{
    HINSTANCE hInst;
    HWND hTool;
    TBADDBITMAP tb;
    int stdid;

    // インスタンスハンドルを取得
    hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWL_HINSTANCE);

    hTool = CreateToolbarEx(
        hWnd,                    // 親ウィンドウ
        WS_CHILD | WS_VISIBLE,   // ウィンドウスタイル
        ID_TOOLBAR,              // コントロールID
        3,                       // イメージの数
        hInst,                   // インスタンスハンドル
        IDR_TOOLBAR1,            // ツールバーのID
        tbb,                     // TBBUTTON構造体
        3,                       // ボタンの数
        0,                       // ボタンの幅
        0,                       // ボタンの高さ
        0,                       // イメージの幅
        0,                       // イメージの高さ
        sizeof(TBBUTTON));

    // TBADDBITMAP構造体のメンバをセットして
    // TB_ADDBITMAPメッセージを送る
    tb.hInst = HINST_COMMCTRL;
    tb.nID = IDB_STD_SMALL_COLOR;
    stdid = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);

    // TBBUTTON構造体のiBitmapメンバを修正し、
    // TB_ADDBUTTONSメッセージを送る
    tbb[3].iBitmap += stdid;
    tbb[4].iBitmap += stdid;
    tbb[5].iBitmap += stdid;
    SendMessage(hTool, TB_ADDBUTTONS, (WPARAM)3, (LPARAM)&tbb[3]);

    // ボタンの系統（VIEW系）が違うので、再度同様の操作をする
    tb.hInst = HINST_COMMCTRL;
    tb.nID = IDB_VIEW_SMALL_COLOR;
    stdid = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);
    tbb[6].iBitmap += stdid;
    SendMessage(hTool, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&tbb[6]);

    // セパレーターの挿入
    SendMessage(hTool, TB_INSERTBUTTON, (WPARAM)3, (LPARAM)&tb_sep);

    return hTool;
}