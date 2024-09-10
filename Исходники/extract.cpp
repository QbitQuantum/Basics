bool Extract(std::list<CString> &ParamList,CConfigManager &ConfigManager,DLL_ID ForceDLL,LPCTSTR lpSpecificOutputDir,const CMDLINEINFO* lpCmdLineInfo)
{
	TRACE(_T("Function ::Extract() started.\n"));
	CConfigGeneral ConfGeneral;
	CConfigExtract ConfExtract;

	ConfGeneral.load(ConfigManager);
	ConfExtract.load(ConfigManager);

	//設定上書き
	if(lpCmdLineInfo){
		if(-1!=lpCmdLineInfo->OutputToOverride){
			ConfExtract.OutputDirType=lpCmdLineInfo->OutputToOverride;
		}
		if(-1!=lpCmdLineInfo->CreateDirOverride){
			ConfExtract.CreateDir=lpCmdLineInfo->CreateDirOverride;
		}
		if(-1!=lpCmdLineInfo->DeleteAfterProcess){
			ConfExtract.DeleteArchiveAfterExtract=lpCmdLineInfo->DeleteAfterProcess;
		}
	}

	//セマフォによる排他処理
	CSemaphoreLocker SemaphoreLock;
	if(ConfExtract.LimitExtractFileCount){
		SemaphoreLock.Lock(LHAFORGE_EXTRACT_SEMAPHORE_NAME,ConfExtract.MaxExtractFileCount);
	}

	UINT uFiles=ParamList.size();	//引数にあるファイルの数

	//プログレスバー
	CProgressDialog dlg;
	//メッセージループを回すためのタイマー
	int timer=NULL;
	if(uFiles>=2){	//ファイルが複数ある時に限定
		dlg.Create(NULL);
		dlg.SetTotalFileCount(uFiles);
		dlg.ShowWindow(SW_SHOW);
		timer=SetTimer(NULL,NULL,1000,UtilMessageLoopTimerProc);
	}

	//指定の出力先
	CPath pathSpecificOutputDir(lpSpecificOutputDir ? lpSpecificOutputDir : _T(""));

	std::vector<ARCLOG> LogArray;	//処理結果を保持
	bool bAllOK=true;	//すべて問題なく解凍されればtrue

	//解凍処理
	for(std::list<CString>::iterator ite_param=ParamList.begin();ite_param!=ParamList.end();++ite_param){
		//プログレスバーを進める
		if(dlg.IsWindow())dlg.SetNextState(*ite_param);

		ARCLOG arcLog;

		//メッセージループ
		while(UtilDoMessageLoop())continue;

		//アーカイバハンドラ取得
		//ここでUNICODE非対応DLLにユニコードファイル名を渡そうとした場合は弾かれる。そして、ここでは失敗の原因を解明できない
		CArchiverDLL *lpArchiver=CArchiverDLLManager::GetInstance().GetArchiver(*ite_param,ConfExtract.DenyExt,ForceDLL);
		if(!lpArchiver){
			//対応するハンドラがなかった
			arcLog.Result=EXTRACT_NOTARCHIVE;
			arcLog.strMsg.Format(IDS_ERROR_ILLEGAL_HANDLER,(LPCTSTR)*ite_param);
			arcLog.strFile=*ite_param;
			bAllOK=false;
			LogArray.push_back(arcLog);
			continue;
		}

		CPath pathOpenDir;		//ファイラが開くべきフォルダ
		//解凍実行
		bool bRet=ExtractOneArchive(ConfigManager,ConfGeneral,ConfExtract,lpArchiver,*ite_param,pathSpecificOutputDir,arcLog,pathOpenDir);
		//ログ保存
		LogArray.push_back(arcLog);

		if(!bRet){
			bAllOK=false;
		}else{
			//出力先フォルダを開く
			if(ConfExtract.OpenDir){
				if(ConfGeneral.Filer.UseFiler){
					//パラメータ展開に必要な情報
					std::map<stdString,CString> envInfo;
					MakeExpandInformationEx(envInfo,pathOpenDir,NULL);

					//コマンド・パラメータ展開
					CString strCmd,strParam;
					UtilExpandTemplateString(strCmd,ConfGeneral.Filer.FilerPath,envInfo);	//コマンド
					UtilExpandTemplateString(strParam,ConfGeneral.Filer.Param,envInfo);	//パラメータ
					ShellExecute(NULL, _T("open"), strCmd,strParam, NULL, SW_SHOWNORMAL);
				}else{
					//Explorerで開く
					UtilNavigateDirectory(pathOpenDir);
				}
			}

			//正常に解凍できた圧縮ファイルを削除orごみ箱に移動
			if(bRet && ConfExtract.DeleteArchiveAfterExtract){
				if(!ConfExtract.ForceDelete && lpArchiver->IsWeakErrorCheck()){
					//エラーチェック機構が貧弱なため、解凍失敗時にも正常と判断してしまうような
					//DLLを使ったときには明示的に指定しない限り削除させない
					MessageBox(NULL,CString(MAKEINTRESOURCE(IDS_MESSAGE_EXTRACT_DELETE_SKIPPED)),UtilGetMessageCaption(),MB_OK|MB_ICONINFORMATION);
				}else{
					//削除
					DeleteOriginalArchives(ConfExtract,*ite_param);
				}
			}
		}
	}
	//プログレスバーを閉じる
	if(dlg.IsWindow())dlg.DestroyWindow();
	//タイマーを閉じる
	if(timer)KillTimer(NULL,timer);

	//---ログ表示
	switch(ConfGeneral.LogViewEvent){
	case LOGVIEW_ON_ERROR:
		if(!bAllOK){
			if(1==uFiles){
				//ファイル一つだけの時はダイアログボックスで
				if(EXTRACT_CANCELED!=LogArray[0].Result){
					ErrorMessage(LogArray[0].strMsg);
				}
			}else{
				//ログに表示
				CLogListDialog LogDlg(CString(MAKEINTRESOURCE(IDS_LOGINFO_OPERATION_EXTRACT)));
				LogDlg.SetLogArray(LogArray);
				LogDlg.DoModal(::GetDesktopWindow());
			}
		}
		break;
	case LOGVIEW_ALWAYS:
		//ログに表示
		CLogListDialog LogDlg(CString(MAKEINTRESOURCE(IDS_LOGINFO_OPERATION_EXTRACT)));
		LogDlg.SetLogArray(LogArray);
		LogDlg.DoModal(::GetDesktopWindow());
		break;
	}

	TRACE(_T("Exit Extract()\n"));
	return bAllOK;
}