//获取数据
HRESULT STDMETHODCALLTYPE CImageDataObject::GetData(FORMATETC * pFormatEtcIn, STGMEDIUM * pStgMedium) 
{
	//状态判断
	ASSERT(m_StgMedium.hBitmap!=NULL);
	if (m_StgMedium.hBitmap==NULL) return E_HANDLE;

	//获取数据
	HANDLE hHandle=OleDuplicateData(m_StgMedium.hBitmap,CF_BITMAP,0);
	if (hHandle==NULL) return E_HANDLE;

	//设置变量
	pStgMedium->tymed=TYMED_GDI;
	pStgMedium->pUnkForRelease=NULL;
	pStgMedium->hBitmap=(HBITMAP)hHandle;

	return S_OK;
}