HBITMAP LoadTransparentImage(wchar_t *fileName)
{
	if (m_pImageFactory != NULL && IsFileExists(fileName) == TRUE)
	{
		IImage*			pImage = NULL;
		IBitmapImage*	pBitmapImage = NULL;
		ImageInfo		imageInfo; 
		BitmapData		bitmapData;

		m_pImageFactory->CreateImageFromFile(fileName, &pImage);
		m_pImageFactory->CreateBitmapFromImage(pImage, 0, 0, 
						PixelFormat32bppPARGB, InterpolationHintNearestNeighbor, 
						&pBitmapImage);
		pImage->GetImageInfo(&imageInfo);  
		RECT rect = {0, 0, imageInfo.Width, imageInfo.Height}; 

		pBitmapImage->LockBits(&rect, ImageLockModeRead, 
								PixelFormat32bppPARGB, &bitmapData);

		return CreateBitmap( imageInfo.Width, imageInfo.Height, 1, 
			GetPixelFormatSize(imageInfo.PixelFormat), bitmapData.Scan0);
	}
	return NULL;
};