//ファイル保存を開始する
//戻り値：
// TRUE（成功）、FALSE（失敗）
//引数：
// fileName				[IN]保存ファイル名
// overWriteFlag		[IN]同一ファイル名存在時に上書きするかどうか（TRUE：する、FALSE：しない）
// createSize			[IN]ファイル作成時にディスクに予約する容量
// saveFolder			[IN]使用するフォルダ一覧
// saveFolderSub		[IN]HDDの空きがなくなった場合に一時的に使用するフォルダ
BOOL CWriteTSFile::StartSave(
	wstring fileName,
	BOOL overWriteFlag,
	ULONGLONG createSize,
	vector<REC_FILE_SET_INFO>* saveFolder,
	vector<wstring>* saveFolderSub,
	int maxBuffCount
)
{
	if( Lock(L"StartSave") == FALSE ) return FALSE;
	BOOL ret = TRUE;

	this->exceptionErr = FALSE;
	this->buffOverErr = FALSE;
	this->maxBuffCount = maxBuffCount;

	if( saveFolder->size() == 0 ){
		UnLock();
		_OutputDebugString(L"CWriteTSFile::StartSave Err saveFolder 0");
		return FALSE;
	}
	
	if( this->outThread == NULL || this->fileList.size() == 0 ){
		this->writeTotalSize = 0;
		this->subRecFlag = FALSE;
		this->saveFileName = fileName;
		this->overWriteFlag = overWriteFlag;
		this->saveFolder = *saveFolder;
		this->saveFolderSub = *saveFolderSub;
		BOOL firstFreeChek = TRUE;
		for( size_t i=0; i<this->saveFolder.size(); i++ ){
			SAVE_INFO* item = new SAVE_INFO;
			if( this->saveFolder[i].writePlugIn.size() == 0 ){
				this->saveFolder[i].writePlugIn = L"Write_Default.dll";
			}
			wstring plugInPath = L"";
			GetModuleFolderPath(plugInPath);
			plugInPath += L"\\Write\\";
			plugInPath += this->saveFolder[i].writePlugIn.c_str();

			item->writeUtil = new CWritePlugInUtil;
			if(item->writeUtil->Initialize(plugInPath.c_str() ) == FALSE ){
				_OutputDebugString(L"CWriteTSFile::StartSave Err 3");
				SAFE_DELETE(item);
			}else{
				wstring folderPath = this->saveFolder[i].recFolder;
				if( CompareNoCase(this->saveFolder[i].writePlugIn, L"Write_Default.dll" ) == 0 ){
					//デフォルトの場合は空き容量をあらかじめチェック
					if( createSize > 0 ){
						if( ChkFreeFolder(createSize, this->saveFolder[i].recFolder) == FALSE ){
							if( GetFreeFolder(createSize, folderPath) == TRUE ){
								//空きなかったのでサブフォルダに録画
								this->subRecFlag = TRUE;
							}
						}
					}
				}
				ChkFolderPath(folderPath);

				wstring recPath;
				recPath = folderPath;
				recPath += L"\\";
				if( this->saveFolder[i].recFileName.size() == 0 ){
					recPath += fileName;
					item->recFileName = fileName;
				}else{
					recPath += this->saveFolder[i].recFileName;
					item->recFileName = this->saveFolder[i].recFileName;
				}
				//開始
				BOOL startRes = item->writeUtil->StartSave(recPath.c_str(), this->overWriteFlag, createSize);
				if( startRes == FALSE ){
					_OutputDebugString(L"CWriteTSFile::StartSave Err 2");
					//エラー時サブフォルダでリトライ
					if( GetFreeFolder(createSize, folderPath) == TRUE ){
						//空きなかったのでサブフォルダに録画
						this->subRecFlag = TRUE;
					}
					ChkFolderPath(folderPath);
					recPath = folderPath;
					recPath += L"\\";
					if( this->saveFolder[i].recFileName.size() == 0 ){
						recPath += fileName;
						item->recFileName = fileName;
					}else{
						recPath += this->saveFolder[i].recFileName;
						item->recFileName = this->saveFolder[i].recFileName;
					}
					startRes = item->writeUtil->StartSave(recPath.c_str(), this->overWriteFlag, createSize);
				}
				if( startRes == TRUE ){
					WCHAR saveFilePath[512] = L"";
					DWORD saveFilePathSize = 512;
					item->writeUtil->GetSaveFilePath(saveFilePath, &saveFilePathSize);

					item->recFilePath = saveFilePath;
					item->freeChk = firstFreeChek;
					item->overWriteFlag = overWriteFlag;
					this->fileList.push_back(item);
					if( i==0 ){
						this->mainSaveFilePath = saveFilePath;
					}
					firstFreeChek = FALSE;
				}else{
					SAFE_DELETE(item);
				}
			}
		}

		if( this->fileList.size() > 0 ){
			//受信スレッド起動
			ResetEvent(this->outStopEvent);
			this->outThread = (HANDLE)_beginthreadex(NULL, 0, OutThread, (LPVOID)this, CREATE_SUSPENDED, NULL);
			SetThreadPriority( this->outThread, THREAD_PRIORITY_NORMAL );
			ResumeThread(this->outThread);
		}else{
			_OutputDebugString(L"CWriteTSFile::StartSave Err fileList 0");
			ret = FALSE;
		}
	}else{
		_OutputDebugString(L"CWriteTSFile::StartSave Err 1");
		ret = FALSE;
	}

	UnLock();
	return ret;
}