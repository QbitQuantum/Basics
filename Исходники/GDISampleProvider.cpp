HRESULT GDISampleProvider::GetSample(IMFSample** ppSample) const
{
	BOOL b = BitBlt(hDest, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
	assert(b);
	BYTE * pixels;
	IMFMediaBufferPtr pBuffer;
	HRESULT hr = MFCreateMemoryBuffer(length, &pBuffer);

	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	if (SUCCEEDED(hr))
		hr = pBuffer->Lock(&pixels, nullptr, nullptr);
	if (SUCCEEDED(hr))
		GetDIBits(hdc, hbDesktop, 0, height, pixels, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);
	if (SUCCEEDED(hr))
		hr = pBuffer->Unlock();
	if (SUCCEEDED(hr))
		hr = pBuffer->SetCurrentLength(cbWidth * VIDEO_HEIGHT);
	if (SUCCEEDED(hr))
		hr = MFCreateVideoSampleFromSurface(nullptr, ppSample);
	if (SUCCEEDED(hr))
		hr = (*ppSample)->AddBuffer(pBuffer);
	return hr;
}