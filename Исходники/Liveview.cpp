//从HGLOBAL数据结构解码得到jpg对象
IPicture *getPicFromHGlobal(HGLOBAL global)
{
	IStream *pStm = NULL;
	IPicture *pPic = NULL;

	HRESULT hr = CreateStreamOnHGlobal(global, TRUE, &pStm);
	
	if (hr != S_OK)
	{
		return NULL;
	}
	hr = OleLoadPicture(pStm, 0, false, IID_IPicture, (LPVOID*)&pPic);
	if (hr != S_OK)
	{
		return NULL;
	}
	return pPic;

}