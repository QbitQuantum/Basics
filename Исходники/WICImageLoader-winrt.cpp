HRESULT WICImageLoader::convertFormatIfRequired(IWICBitmapFrameDecode* pFrame, IWICFormatConverter** ppConv)
{
	*ppConv = NULL;

	if(	(memcmp(&_format, &GUID_WICPixelFormat8bppGray, sizeof(WICPixelFormatGUID)) == 0) ||
		(memcmp(&_format, &GUID_WICPixelFormat8bppAlpha, sizeof(WICPixelFormatGUID)) == 0) ||
		(memcmp(&_format, &GUID_WICPixelFormat24bppRGB, sizeof(WICPixelFormatGUID)) == 0) ||
		(memcmp(&_format, &GUID_WICPixelFormat32bppRGBA, sizeof(WICPixelFormatGUID)) == 0))
	{
		return S_OK;
	}

	HRESULT hr = E_FAIL;
	IWICImagingFactory* pFactory = getWICFactory();
	IWICFormatConverter* pConv = NULL;

	if(NULL != pFactory)
	{
		hr = pFactory->CreateFormatConverter(&pConv);
	}

	WICPixelFormatGUID destFormat = GUID_WICPixelFormat32bppRGBA; // Fallback to RGBA 32-bit format which is supported by all devices

	for( size_t i=0; i < _countof(g_WICConvert); ++i )
	{
		if ( memcmp( &g_WICConvert[i].source, &_format, sizeof(WICPixelFormatGUID) ) == 0 )
		{
			memcpy( &destFormat, &g_WICConvert[i].target, sizeof(WICPixelFormatGUID) );
			break;
		}
	}

	BOOL bCanConv = FALSE;

	if(SUCCEEDED(hr))
	{
		hr = pConv->CanConvert(_format, destFormat, &bCanConv);
	}

	if(SUCCEEDED(hr) && bCanConv == TRUE)
	{
		hr = pConv->Initialize(pFrame, destFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
	}

	if(SUCCEEDED(hr))
	{
		memcpy(&_format, &destFormat, sizeof(WICPixelFormatGUID));
		*ppConv = pConv;
	}

	return SUCCEEDED(hr);
}