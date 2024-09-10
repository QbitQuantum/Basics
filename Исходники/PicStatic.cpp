HRESULT CPicStatic::ShowJpeg(LPVOID picData,DWORD dwFileSize,int x, int y,CDC *pDC)
{
	IStream   *pStm;
	IPicture   *pPic;
	BOOL   bResult;     
   
	HGLOBAL   hGlobal   =   GlobalAlloc(GMEM_MOVEABLE,   dwFileSize);     
	LPVOID   pvData   =   NULL;
	if (hGlobal  ==   NULL)
		return   false;
	pvData   =   GlobalLock(hGlobal);
	if ( pvData ==   NULL)  
		return   false;

	memcpy(pvData,picData,dwFileSize);
	GlobalUnlock(hGlobal);
	CreateStreamOnHGlobal(hGlobal,   TRUE,   &pStm);
	bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);

	if(FAILED(bResult))
	{
//		CloseHandle(hFile);
		return   false;
	}
	OLE_XSIZE_HIMETRIC   hmWidth;
	OLE_YSIZE_HIMETRIC   hmHeight;
	pPic->get_Width(&hmWidth);     
	pPic->get_Height(&hmHeight);     
	//将图形输出到屏幕上（有点像BitBlt）     
	bResult=pPic->Render(pDC->m_hDC,0,0,x,y,0,hmHeight,hmWidth,-hmHeight,NULL);     

//	CloseHandle(hFile);
	pStm->Release();
	pPic->Release();
	if   (SUCCEEDED(bResult))     
	{
		return   S_OK;     
	}     
	else     
	{     
		return   E_FAIL;     
	}   
}