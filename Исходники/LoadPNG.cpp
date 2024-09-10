// Loads a PNG image from the specified stream (using Windows Imaging Component).
IWICBitmapSource * LoadBitmapFromStream(IStream * ipImageStream)
{
	// initialize return value
	IWICBitmapSource * ipBitmap = NULL;

	// load WIC's PNG decoder
	IWICBitmapDecoder * ipDecoder = NULL;
	IID i = IID_IWICBitmapDecoder;

	if (FAILED(CoCreateInstance(CLSID_WICPngDecoder, NULL, CLSCTX_INPROC_SERVER,
		i,//__uuidof(ipDecoder)

		(void **)&ipDecoder)))
		goto Return;


	// load the PNG
	if (FAILED(ipDecoder->Initialize(ipImageStream, WICDecodeMetadataCacheOnLoad)))
		goto ReleaseDecoder;

	// check for the presence of the first frame in the bitmap
	UINT nFrameCount = 0;

	if (FAILED(ipDecoder->GetFrameCount(&nFrameCount)) || nFrameCount != 1)
		goto ReleaseDecoder;

	// load the first frame (i.e., the image)
	IWICBitmapFrameDecode * ipFrame = NULL;

	if (FAILED(ipDecoder->GetFrame(0, &ipFrame)))
		goto ReleaseDecoder;


	// convert the image to 32bpp BGRA format with pre-multiplied alpha
	//   (it may not be stored in that format natively in the PNG resource,
	//   but we need this format to create the DIB to use on-screen)
	WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, ipFrame, &ipBitmap);
	ipFrame->Release();

ReleaseDecoder:
	ipDecoder->Release();

Return:
	return ipBitmap;

}