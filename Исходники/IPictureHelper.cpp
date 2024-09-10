CLIB_API IPicture * GetIPictureFromBitmap(HBITMAP hBitmap)
{
	PICTDESC pd;
	pd.cbSizeofstruct=sizeof(PICTDESC);
	pd.picType=PICTYPE_BITMAP;
	pd.bmp.hbitmap=hBitmap;
	pd.bmp.hpal=NULL;
	IPicture* iPicture = NULL;
	if (SUCCEEDED(OleCreatePictureIndirect(&pd,IID_IPicture,TRUE,(LPVOID*)&iPicture)))
		return iPicture;
	// failed
	DeleteObject((HGDIOBJ)hBitmap);
	return NULL;
}