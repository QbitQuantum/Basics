//パスに共通する部分を取り出し、基底パスを取り出す
void UtilGetBaseDirectory(CString &BasePath,const std::list<CString> &PathList)
{
	bool bFirst=true;
	size_t ElementsCount=0;	//共通項目数
	std::vector<CString> PathElements;	//共通項目の配列

	std::list<CString>::const_iterator ite,end;
	end=PathList.end();
	for(ite=PathList.begin();ite!=end;++ite){
		if(!bFirst&&0==ElementsCount){
			//既に共通している要素が配列内に存在しないとき
			break;
		}

		//親ディレクトリまでで終わるパスを作る
		TCHAR Path[_MAX_PATH+1];
		FILL_ZERO(Path);
		_tcsncpy_s(Path,*ite,_MAX_PATH);
		PathRemoveFileSpec(Path);
		PathAddBackslash(Path);

		CString buffer;
		size_t iElement=0;	//一致しているパスの要素のカウント用(ループ内)
		size_t iIndex=0;	//パス内の文字のインデックス
		const size_t Length=_tcslen(Path);
		for(;iIndex<Length;iIndex++){
#if !defined(_UNICODE)&&!defined(UNICODE)
			if(_MBC_SINGLE==_mbsbtype((const unsigned char *)Path,iIndex)){
#endif
				if(_T('\\')==Path[iIndex]){
					//初回ならパスを詰め込み、そうでなければ要素を比較
					if(bFirst){
						PathElements.push_back(buffer);
						buffer.Empty();
						continue;
					}
					else{
						//大文字小文字区別せずに比較
						if(0==PathElements[iElement].CompareNoCase(buffer)){
							//要素が共通しているうちはOK
							iElement++;
							if(iElement>=ElementsCount)break;
							else{
								buffer.Empty();
								continue;
							}
						}
						else
						{
							//要素数を減らす
							//0オリジンのi番目で不一致ならばi個まで一致
							ElementsCount=iElement;
							break;
						}
					}
				}
#if !defined(_UNICODE)&&!defined(UNICODE)
			}
#endif
			buffer+=Path[iIndex];
		}
		if(bFirst){
			bFirst=false;
			ElementsCount=PathElements.size();
		}
		else if(ElementsCount>iElement){
			//パスが短かった場合、不一致なしのまま処理が終了する場合がある
			ElementsCount=iElement;
		}
	}

	BasePath.Empty();
	for(size_t i=0;i<ElementsCount;i++){
		BasePath+=PathElements[i];
		BasePath+=_T("\\");
	}
	TRACE(_T("BasePath=%s\n"),BasePath);
}