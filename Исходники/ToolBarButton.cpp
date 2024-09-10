///////////////////////////////////////////////////////////////////////////////
// ein IPicture aus eine Bitmap erzeugen
HRESULT CreatePicture (HBITMAP hBmp, HPALETTE hPal, bool fOwn, IPictureDisp **ppIDisp)
{
COlePro32Bind Wrap;		// OlePro32.dll dynamisch laden und binden

	if (!Wrap.IsValid()) return E_UNEXPECTED;

PICTDESC pdesc;
WDispatch Disp;

	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.picType = PICTYPE_BITMAP;
	pdesc.bmp.hbitmap = hBmp;
	pdesc.bmp.hpal = hPal;

HRESULT hr = Wrap.OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, fOwn, (LPVOID *)ppIDisp);

	if (FAILED(hr)) {
		::DeleteObject (hBmp);
		return hr;
	}
	return S_OK;
}