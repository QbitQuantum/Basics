//===========================================================================
// 暗号化するファイルリストとファイル情報のリストを同時生成する
//===========================================================================
__int64 __fastcall TAttacheCaseFileEncrypt::GetFileInfoList
	( int &Index,
		String DirPath,
		String FileName,
		String BasePath,
		TStringList *FileList,
		TStringList *DataList
	)
{

/* ------------------------------------------------
 ファイルリストのファイル番号の頭に「Fn_*:」と
 なぜ重複するような記号が挿入されているかと言いますと
 あまり意味はございません・・・お恥ずかしいかぎり・・・
 すみません、これもver.1からの仕様を引きずっているのと、
 習作時代にやっちゃった無意味なデータ仕様の一つです。
--------------------------------------------------- */

int ret;
__int64 TotalSize = 0;

bool fParent = false;
String OneLine;
String FilePath;
String FileNameString;

TSearchRec sr;
//_WIN32_FIND_DATAW fd;

DirPath = IncludeTrailingPathDelimiter(DirPath);

if (FileName == "") {  //ディレクトリ
	FileName = "*.*";
}
else{
	fParent = true;
}

ret = FindFirst(DirPath + FileName, faAnyFile, sr);

while (ret == 0) {

	if (sr.Name != "." && sr.Name != "..") {

		FilePath = DirPath + sr.Name;
		FileNameString = ExtractRelativePath(BasePath, FilePath);

		//-----------------------------------
		//ディレクトリ
		if (sr.Attr & faDirectory) {

			// Win95/98系（非対応だが一応）
			if ( Win32Platform == VER_PLATFORM_WIN32_WINDOWS ){
				OneLine =
					"Fn_" + IntToStr((int)Index) + ":" +                 //インデックス
					FileNameString + "\\\t" +                            //ディレクトリ名
					"*\t16\t0\t0\t0\t0";                                 //残りは0
			}
			else{
				// _WIN32_FIND_DATAW 構造体
				//fd = sr.FindData;
				OneLine =
					"Fn_" + IntToStr((int)Index) + ":" +                 //インデックス
					FileNameString + "\\\t" +                            //ディレクトリの相対パス
					"*\t" +                                              //ファイルサイズ(=0)
					IntToStr(sr.Attr) + "\t" +                           //属性
					TimeStampToString(sr.FindData.ftLastWriteTime)+"\t"+ //更新日時
					TimeStampToString(sr.FindData.ftCreationTime);       //作成日時

					//出力する暗号化ファイルのタイムスタンプを元ファイルに合わせるため保持
					if ( fKeepTimeStamp == true && first_fd.cFileName[0] == NULL ) {
						first_fd = sr.FindData;
					}

			}

			FileList->Add("");      //ディレクトリは空行
			DataList->Add(OneLine);
			Index++;

			if (fParent == false) {
				//再帰呼び出し
				TotalSize += GetFileInfoList(Index, FilePath, "", BasePath, FileList, DataList);
			}

		}
		//-----------------------------------
		//ファイル
		else{
			OneLine =
				"Fn_" + IntToStr((int)Index) + ":" +                   //インデックス
				FileNameString + "\t" +                                //ファイルの相対パス
				IntToStr(sr.Size) + "\t" +                             //ファイルサイズ
				IntToStr(sr.Attr) + "\t" +                             //属性
				TimeStampToString(sr.FindData.ftLastWriteTime)+"\t"+   //更新日時
				TimeStampToString(sr.FindData.ftCreationTime);         //作成日時

			//出力する暗号化ファイルのタイムスタンプを元ファイルに合わせるため保持
			if ( fKeepTimeStamp == true && first_fd.cFileName[0] == NULL ) {
				first_fd = sr.FindData;
			}

			if (sr.Size > 0) {
				FileList->Add(FilePath);
			}
			else{
				FileList->Add("");      //空ファイルは加えない
			}

			DataList->Add(OneLine);
			Index++;

			//ファイル総計
			TotalSize += sr.Size;

		}
		//-----------------------------------

	}//end if;

	ret = FindNext(sr);

}//while;

FindClose(sr);

return(TotalSize);


}//end GetFileInfoList;