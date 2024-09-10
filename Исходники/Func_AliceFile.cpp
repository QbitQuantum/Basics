// Game_FileHeaderクラスのポインタを渡すと、
// その内容に指定したインデックスのファイルのファイルヘッダを読み込む。
bool GetGameFileHeader(Game_FileHeader* pHeader, BYTE index){
	TCHAR fileName[SIZE_SAVEFILENAME];
	// ファイル名を取得する
	if(!GetSaveGameFileName(fileName, SIZE_SAVEFILENAME, index)){
		return false;
	}
	// ファイルが存在するかどうか判定する
	if(!GetGameFileIsExist(index)){
		return false;
	}
	// MyFilesクラス
	MyFiles			file;
	// ファイルを開く
	if(!file.LoadFilesFromDat(fileName)){
		return false;
	}
	// 復号化
	file.EncodeFileXOR(
		SAVEFILE_INDEX_FILEHEADER, 
		_T(SAVEFILE_CODE_FILEHEADER), (WORD)strlen(_T(SAVEFILE_CODE_FILEHEADER)));
	// ポインタの取得
	LPVOID pData = file.GetFilePointerByIndex(SAVEFILE_INDEX_FILEHEADER);
	// ファイルサイズが正しいかどうかの確認
	DWORD fileSize = file.GetFileSize(SAVEFILE_INDEX_FILEHEADER);
	// データの読み込み
	if(!pHeader->LoadFromBytes(pData, fileSize)){
		return false;
	}
	return true;
}