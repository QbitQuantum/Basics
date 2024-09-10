ID2D1Bitmap * BaseButton::LoadBitmap(wchar_t* sz_path)
{
	ID2D1Bitmap *p_bmp=NULL;
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;
	HRESULT hr;
	hr = g_pIWICFactory->CreateDecoderFromFilename(sz_path,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&pDecoder);
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = g_pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		UINT originalWidth, originalHeight;
		hr = pSource->GetSize(&originalWidth, &originalHeight);
	}
	if (SUCCEEDED(hr))
	{

		hr =g_pIWICFactory->CreateBitmapScaler(&pScaler);
	}
	if (SUCCEEDED(hr))
	{
		hr = pScaler->Initialize(pSource,50,30,WICBitmapInterpolationModeCubic);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(pScaler,GUID_WICPixelFormat32bppPBGRA,WICBitmapDitherTypeNone,NULL,0.f,WICBitmapPaletteTypeMedianCut);
	}
	
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr =m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter,NULL,&p_bmp);
	}
	
	
	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
// 	if (SUCCEEDED(hr))
// 	{
// 		return TRUE;
// 	}
// 	else
// 		return FALSE;
	return p_bmp;
}