bool CLoadBmp::Read(const CString &strType,	IW::IStreamIn *pStreamIn, IW::IImageStream *pImageOut, IW::IStatus *pStatus)
{
	IW::MetaData data;
	HRESULT hr = data.LoadFromStream(pStreamIn);

	if (FAILED(hr)) 
		return false;

	DWORD nSize = data.GetDataSize();
	LPBYTE  pByte = data.GetData();	
	

	// Read the file header to get the file size and to
	// find out where the bits start in the 
	BITMAPFILEHEADER *pBmpFileHdr = (BITMAPFILEHEADER*)(LPBYTE)pByte;
	
	// Dib Header
	BITMAPINFO *pInfo = (BITMAPINFO*)(pByte + sizeof(BITMAPFILEHEADER));
	
    // Check that we got a real Windows DIB 
    if (pInfo->bmiHeader.biSize != sizeof(BITMAPINFOHEADER)) 
	{
		
		return FALSE;
	}
	
	// I only want single plain headers 
    if (pInfo->bmiHeader.biPlanes != 1) 
	{		
		return FALSE;
	}
	
	IW::PixelFormat pf = IW::PixelFormat::FromBpp(pInfo->bmiHeader.biBitCount);
	UINT nWidth = pInfo->bmiHeader.biWidth;
	UINT nHeight = pInfo->bmiHeader.biHeight;
	int nStorageWidth = IW::CalcStorageWidth(nWidth, pf);
	
	LPRGBQUAD pRgb = (LPRGBQUAD)((LPSTR)pInfo + (WORD)(pInfo->bmiHeader.biSize)); 
	UINT nColors = pInfo->bmiHeader.biClrUsed; 
	
	if (nColors == 0)
	{
		nColors = pf.NumberOfPaletteEntries();
	}
	
	assert(nHeight > 0);	
	
	// We really need to calculate the bfOffBits
	// ourselves as if it is corrupt a GPF may occure!
	LPBYTE pBitmap = (LPBYTE)(pRgb + nColors);

	int nBytesMax = nSize - (pBitmap - pByte);

	if (nBytesMax < 0)
	{
		return false;
	}

	IW::Image image;
	
	if (!image.Copy(pInfo, pBitmap, nBytesMax))
	{		
		return false;
	}

	IW::IterateImage(image, *pImageOut, pStatus);

	// Information
	CString strInformation;
	strInformation.Format(IDS_BMP_FMT, nWidth, nHeight, pf.ToBpp());
	
	IW::CameraSettings settings;
	settings.XPelsPerMeter = pInfo->bmiHeader.biXPelsPerMeter;
	settings.YPelsPerMeter = pInfo->bmiHeader.biYPelsPerMeter;
	settings.OriginalImageSize.cx = nWidth;
	settings.OriginalImageSize.cy = nHeight;
	settings.OriginalBpp = pf;

	pImageOut->SetCameraSettings(settings);
	pImageOut->SetLoaderName(GetKey());	
	pImageOut->SetStatistics(strInformation);

	return true;
}