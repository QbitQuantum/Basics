BOOL GdiplusUtilities::CreateThumbnail(LPCTSTR srcFile, LPCTSTR thumbnailFile, ImageFormatEnum imageFormat, INT cx, INT cy)
{
	Gdiplus::Bitmap* pSrcImage = Gdiplus::Bitmap::FromFile(srcFile, FALSE);
	if (pSrcImage == NULL)
		return FALSE;


	//=== Default function...stretches the image
	Gdiplus::Image* pDestImage = pSrcImage->GetThumbnailImage(cx, cy);
	
	delete pSrcImage;

	CLSID pngClsid;

	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, _T("image/png")) == 0 )
		{
			pngClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			Gdiplus::Status st = pDestImage->Save(thumbnailFile, &pngClsid, NULL);
			return st == Gdiplus::Ok;
		}    
	}

	free(pImageCodecInfo);
	
	return FALSE;


}