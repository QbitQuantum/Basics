/*!
 @brief このメソッドは WM_INITDIALOG のメッセージに応答して呼び出されます。
*/
BOOL CInspectUsefulToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	//SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// メニューの初期化
	InitializeMenuTree();
	InitializeContents();

	// タイトルの設定
	CString strAppName = CString((LPCTSTR)IDS_APP_NAME);
	this->SetWindowText(strAppName);

	CLSID clsid;
	if (CLSIDFromProgID(OLESTR("Excel.Application"), &clsid) == NOERROR){
		// Excel がインストールされている
		LPUNKNOWN lpUnk;
		HRESULT hr;
		LPDISPATCH lpDispatch;
		BOOL bOpenExcel = FALSE;
		if (GetActiveObject(clsid, NULL, &lpUnk) == NOERROR){
			hr = lpUnk->QueryInterface(IID_IDispatch, (LPVOID*)&lpDispatch);
			lpUnk->Release();
			if (hr == NOERROR) {
				//すでにExcelが起動されている状態であればAttachDispatch
				m_inXLApp.AttachDispatch(lpDispatch,TRUE);
				bOpenExcel = TRUE;
			}
		}

		if (m_inXLApp.m_lpDispatch == NULL) {
			bOpenExcel = m_inXLApp.CreateDispatch(clsid);
			m_bOpenXL = TRUE;
		}

		if (bOpenExcel == TRUE) {
			// Excelファイルの初期化
			CWorkbooks inWorkbooks = m_inXLApp.get_Workbooks();
			COleVariant varNull;
			varNull.ChangeType(VT_NULL);

			HRSRC hrSrc = FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MACRO_EXCEL_RCDATA), RT_RCDATA);
			if (hrSrc != NULL) {
				HGLOBAL hGlobal = LoadResource(AfxGetApp()->m_hInstance, hrSrc);

				if (hGlobal != NULL) {
					char *rcData = (char *)LockResource(hGlobal);

					/* リソースサイズの取得 */
					DWORD dwSize = SizeofResource(AfxGetApp()->m_hInstance, hrSrc);

					TCHAR szFilePath[MAX_PATH];
					GetTempPath(MAX_PATH, szFilePath);
					TCHAR szFileName[MAX_PATH];
					GetTempFileName(szFilePath, _T("SubTools_"), 0, szFileName);

					CFile inFile;
					inFile.Open(szFileName, CFile::modeWrite);
					inFile.Write(rcData, dwSize);
					inFile.Close();
					strTempFilePath = szFileName;

					m_inXLBook = inWorkbooks.Open(szFileName
						, varNull, varNull, varNull, varNull, varNull, varNull, varNull, varNull, varNull, varNull, varNull, varNull,varNull, varNull);
					m_bOpenBook = TRUE;
				}
			}
		}
	}

	return TRUE;
}