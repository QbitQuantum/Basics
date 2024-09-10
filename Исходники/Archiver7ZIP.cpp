//=============================================================
// SevenZipGetFileName()の出力結果を基に、格納されたファイルが
// パス情報を持っているかどうか判別し、二重フォルダ作成を防ぐ
//=============================================================
bool CArchiver7ZIP::ExamineArchive(LPCTSTR ArcFileName,CConfigManager& ConfMan,bool bSkipDir,bool &bInFolder,bool &bSafeArchive,CString &BaseDir,CString &strErr)
{
	//UNICODE文字が安全かどうか判定する
	ASSERT(IsOK());
	if(!IsOK()){
		return false;
	}

	if(!InspectArchiveBegin(ArcFileName,ConfMan)){
		strErr.Format(IDS_ERROR_OPEN_ARCHIVE,ArcFileName);
		return false;
	}

	bInFolder=true;
	bool bSureDir=false;	//BaseDirに入っている文字列が確かにフォルダであるならtrue
	TRACE(_T("========\n"));

	while(InspectArchiveNext()){
		CString Buffer;
		InspectArchiveGetFileName(Buffer);
		Buffer.Replace(_T('\\'),_T('/'));		//パス区切り文字の置き換え
		TRACE(_T("%s\n"),Buffer);

		/*
		Separator('/' or '\')は格納ファイルの先頭にいくら含まれていても無視すべきであるので、
		格納ファイル名の先頭にいくらSeparatorがあってもフォルダに格納された状態とは見なさない。
		SeparatorがMaxRepeatより多いと不正とする
		ただし、MaxRepeatが-1のときはエラーとはしない
		*/
		const int Length=Buffer.GetLength();
		int StartIndex=0;
		for(;StartIndex<Length;StartIndex++){
			//先頭の'/'をとばしていく
#if defined(_UNICODE)||defined(UNICODE)
			if(_T('/')!=Buffer[StartIndex])break;
#else
			if(_MBC_SINGLE==_mbsbtype((const unsigned char *)(LPCTSTR)Buffer,StartIndex)){
				if(_T('/')!=Buffer[StartIndex])break;
			}
			else{	//全角文字なら'/'であるはずがない
				break;
			}
#endif//defined(_UNICODE)||defined(UNICODE)
		}
		if(!UtilIsSafeUnicode((LPCTSTR)Buffer+StartIndex)){	//危険なUNICODE指定が見つかれば、危険なファイルと見なす
			//監査終了
			InspectArchiveEnd();
			bSafeArchive=false;
			bInFolder=false;
			return true;
		}

		//ここからは二重ディレクトリ判定
		//すでに二重ディレクトリ判定が付いている場合は安全判定のみに徹する

		int FoundIndex=0;
		while(bInFolder){
			FoundIndex=Buffer.Find(_T('/'),StartIndex);
			if(-1==FoundIndex){	//'/'が格納ファイル名の先頭以外に含まれない場合
				if(!BaseDir.IsEmpty()&&BaseDir==Buffer){
					bSureDir=true;	//BaseDirがフォルダであると確認された
					break;
				}
				else if(BaseDir.IsEmpty()){
					//フォルダ名の後ろに'/'が付かないアーカイバもある
					//そういうものが最初に出てきたときは、フォルダ名と仮定する
					BaseDir=Buffer;
					bSureDir=false;
					break;
				}
			}
			CString Dir=Buffer.Mid(StartIndex,FoundIndex-StartIndex);	//Separatorの前までの文字列(ディレクトリに相当)を抜き出してくる
			//これまでの調べでDirはEmptyではないことが保証されている
			//また、危険ではないことも分かっている
			TRACE(_T("Base=%s,Dir=%s\n"),BaseDir,Dir);

			if(_T('.')==Dir){	//./があればディレクトリ指定としては無視する
				StartIndex=FoundIndex+1;
				continue;
			}
			if(BaseDir.IsEmpty()){
				BaseDir=Dir;
				bSureDir=true;
			}
			else if(BaseDir!=Dir){
				bInFolder=false;
			}
			else bSureDir=true;	//BaseDirがディレクトリと確認された
			break;
		}
	}
	TRACE(_T("========\n"));

	InspectArchiveEnd();
	bSafeArchive=true;

	//フォルダに入っているようではあるが、ディレクトリと仮定されただけの場合
	if(bInFolder&&!bSureDir)bInFolder=false;
	return true;
}