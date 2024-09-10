bool TestArchive(const std::list<CString> &rArcList,CConfigManager &ConfigManager)
{
	CArchiverDLLManager &ArchiverManager=CArchiverDLLManager::GetInstance();

	//XacRettはチェックが甘いため使わない

	//プログレスバー
	CProgressDialog dlg;
	int nFiles=rArcList.size();
	dlg.Create(NULL);
	dlg.SetTotalFileCount(nFiles);
	dlg.ShowWindow(SW_SHOW);


	std::list<CString>::const_iterator ite=rArcList.begin();
	const std::list<CString>::const_iterator end=rArcList.end();

	//テスト結果を格納する
	std::vector<ARCLOG> LogArray;
	for(;ite!=end;++ite){
		//プログレスバーを進める
		if(dlg.IsWindow())dlg.SetNextState(*ite);

		ARCLOG arcLog;
		arcLog.strFile=*ite;
		//アーカイバハンドラ取得
		//NOTE:DenyExtによる対象絞り込みは既に行われているので2回は行わない
		CArchiverDLL *Archiver=ArchiverManager.GetArchiver(*ite,NULL);

		if(!Archiver){
			//---対応するハンドラがなかった:原因を調査
			//通常のエラー
			arcLog.strMsg.Format(IDS_ERROR_ILLEGAL_HANDLER,*ite);
			arcLog.Result=TEST_NOTARCHIVE;

			//UNICODE関係のチェック
			if(!UtilCheckT2A(*ite)){
				//UNICODEに対応していないのにUNICODEファイル名のファイルを扱おうとした
				arcLog.strMsg+=_T("\r\n\r\n");
				arcLog.strMsg.AppendFormat(IDS_ERROR_UNICODEPATH);
			}
		}else{
			CString strTemp;
			arcLog.Result=Archiver->TestArchive(*ite,strTemp);
			arcLog.strMsg=Archiver->GetName();
			arcLog.strMsg+=_T("\r\n\r\n");
			arcLog.strMsg+=strTemp;
		}
		LogArray.push_back(arcLog);
	}
	//プログレスバーを閉じる
	if(dlg.IsWindow())dlg.DestroyWindow();

	//ログに表示
	CLogListDialog LogDlg(CString(MAKEINTRESOURCE(IDS_LOGINFO_OPERATION_TESTARCHIVE)));
	LogDlg.SetLogArray(LogArray);
	LogDlg.DoModal(::GetDesktopWindow());

	return true;
}