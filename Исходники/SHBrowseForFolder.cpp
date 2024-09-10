// =============================================
// CallbackSelectDir
// 概要  : フォルダ参照で使用するコールバック関数
//       : 開いたときにフォルダを選択した状態で開かせる処理をする場合に必要
// 引数  : ...
// 戻り値: int CALLBACK
// =============================================
int CALLBACK CSHBrowseForFolder::CallbackSelectDir(HWND hWnd, UINT uMsg, LPARAM, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED) {
		// デフォルトのフォルダを選択させる
		SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
		{
			// フォルダーツリーで常に選択状態を表示
			HWND hwndTree = FindWindowEx(hWnd, NULL, "SysTreeView32", NULL);
			if (hwndTree != NULL) {
				LONG style;
				style = GetWindowLong(hwndTree, GWL_STYLE);
				style |= TVS_SHOWSELALWAYS;
				SetWindowLong(hwndTree, GWL_STYLE, style);
			}
		}

		// [サブディレクトリを検索] ボタンを追加
		if (GetEnableSubDirButton()) {
			pSubDir = new CButton; /* WildCherry2 080 */
			if (pSubDir) {
				RECT	rectClient, rectOK, rectCancel, rect;
				CWnd	*pClient	= CWnd::FromHandle(hWnd);
				CWnd	*pOK		= pClient->GetDlgItem(IDOK);
				CWnd	*pCANCEL	= pClient->GetDlgItem(IDCANCEL);
				// クライアントウィンドウサイズを取得
				pClient->GetClientRect(&rectClient);
				// [OK] / [CANCEL] のウィンドウ位置を取得
				pOK->GetWindowRect(&rectOK);
				pCANCEL->GetWindowRect(&rectCancel);
				pClient->ScreenToClient(&rectOK) ;
				pClient->ScreenToClient(&rectCancel) ;
				// サブディレクトリ対象チェックボタンの RECT を求める
				rect = CRect(rectClient.right - rectCancel.right,
				             rectCancel.top,
				             rectOK.left,
				             rectCancel.bottom);
				// チェックボタン作成
				if (pSubDir->Create(GetCheckBoxTitle(),
				                    WS_CHILD | WS_VISIBLE | BS_CHECKBOX | WS_TABSTOP,
				                    rect, pClient, IDC_CH_SUB_DIR)) {
					// フォントを設定
					HFONT hFontCurr = (HFONT)pClient->SendMessage(WM_GETFONT, 0, 0);
					if (hFontCurr != NULL) pSubDir->PostMessage(WM_SETFONT, (WPARAM)hFontCurr, 0); 

					// チェック状態を設定
					pSubDir->SetCheck(GetSearchSubDirState() ? TRUE : FALSE);

					// サブクラス化
					m_VSSelectOrgProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)VSSelectFolderSubProc);
				}
			}
		}
	}
	return 0;
}