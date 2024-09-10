void VPictureData_EMF::FromMetaFilePict(METAFILEPICT* inMetaPict)
{
	HENHMETAFILE henh;
	_ReleaseDataProvider();
	_DisposeMetaFile();
	
	void*        lpWinMFBits;
	UINT         uiSizeBuf;

	uiSizeBuf = GetMetaFileBitsEx(inMetaPict->hMF, 0, NULL);
	lpWinMFBits = GlobalAllocPtr(GHND, uiSizeBuf);
	GetMetaFileBitsEx(inMetaPict->hMF, uiSizeBuf, (LPVOID)lpWinMFBits);
	henh = SetWinMetaFileBits(uiSizeBuf, (LPBYTE)lpWinMFBits, NULL, inMetaPict);
	GlobalFreePtr(lpWinMFBits);


	FromEnhMetaFile(henh);
}