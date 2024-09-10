BOOL CDShowCtrl::SetMuxerProp()
{
	if( this->muxer == NULL ){
		return FALSE;
	}
	BOOL ret = TRUE;

	ISpecifyPropertyPages *prop = NULL;
	HRESULT hr = this->muxer->QueryInterface(IID_ISpecifyPropertyPages, (void**)&prop);
    if (FAILED(hr)){
		return FALSE;
	}

	FILTER_INFO FilterInfo;
	this->muxer->QueryFilterInfo(&FilterInfo);

	CAUUID caGUID;
	prop->GetPages(&caGUID);

	OleCreatePropertyFrame(
		NULL,                   // 親ウィンドウ
		0,                      // x (予約済み)
		0,                      // y (予約済み)
		FilterInfo.achName,     // ダイアログ ボックスのキャプション
		1,                      // フィルタの数
		(IUnknown **)&this->muxer,  // フィルタへのポインタ
		caGUID.cElems,          // プロパティ ページの数
		caGUID.pElems,          // プロパティ ページ CLSID へのポインタ
		0,                      // ロケール識別子
		0,                      // 予約済み
		NULL                    // 予約済み
	);
	CoTaskMemFree(caGUID.pElems);

	SAFE_RELEASE(prop);

	return ret;
}