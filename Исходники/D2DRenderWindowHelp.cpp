//etc. WICConvertBitmapSource
BOOL ConvertWICBitmapFormat(IWICImagingFactory* pWICFactory,REFWICPixelFormatGUID toFormat,IWICBitmapSource* pSrc,IWICBitmapSource** ppDst)
{
	IWICFormatConverter* pWICFormatConverter;
	if (FAILED(pWICFactory->CreateFormatConverter(&pWICFormatConverter)))
		return FALSE;
	if (SUCCEEDED(pWICFormatConverter->Initialize(pSrc,toFormat,WICBitmapDitherTypeNone,NULL,.0f,WICBitmapPaletteTypeCustom)))
	{
		*ppDst = pWICFormatConverter;
		return TRUE;
	}
	return FALSE;
}