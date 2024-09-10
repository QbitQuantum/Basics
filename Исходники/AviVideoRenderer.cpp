/*
---------------------------------------------------------------------------------------
- Opens An AVI File (szFile)
---------------------------------------------------------------------------------------
*/
bool AviVideoRenderer::OpenAVI(const char * szFile)
{
	// Opens The AVI Stream
	if (AVIStreamOpenFromFileA(&_AVR_pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL) !=0)
		return false;

	AVIStreamInfo(_AVR_pavi, &_AVR_psi, sizeof(_AVR_psi));						// Reads Information About The Stream Into psi
	_video_width=_AVR_psi.rcFrame.right-_AVR_psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
	_video_height=_AVR_psi.rcFrame.bottom-_AVR_psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top

	_endFrame=AVIStreamLength(_AVR_pavi);							// The Last Frame Of The Stream

	_timeperframe=AVIStreamSampleToTime(_AVR_pavi,_endFrame)/_endFrame;		// Calculate Rough Milliseconds Per Frame


	int sizet = 1024;
	if((_video_width < 128) && (_video_height < 128))
		sizet = 128;
	else if((_video_width < 256) && (_video_height < 256))
		sizet = 256;
	else if((_video_width < 512) && (_video_height < 512))
		sizet = 512;

	_widths.push_back(sizet);
	_heights.push_back(sizet);

	// initialize the host texture
	InitializeTexture();


	_AVR_bmih.biSize = sizeof (BITMAPINFOHEADER);					// Size Of The BitmapInfoHeader
	_AVR_bmih.biPlanes = 1;											// Bitplanes
	_AVR_bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
	_AVR_bmih.biWidth = _widths[0];									// Width We Want
	_AVR_bmih.biHeight = _heights[0];								// Height We Want
	_AVR_bmih.biCompression = BI_RGB;								// Requested Mode = RGB

	_AVR_hBitmap = CreateDIBSection (_AVR_hdc, (BITMAPINFO*)(&_AVR_bmih), DIB_RGB_COLORS, (void**)(&_img_data), NULL, NULL);
	SelectObject (_AVR_hdc, _AVR_hBitmap);							// Select hBitmap Into Our Device Context (hdc)

	_AVR_pgf=AVIStreamGetFrameOpen(_AVR_pavi, NULL);				// Create The PGETFRAME	Using Our Request Mode


	_avi_opened = true;

	return(_AVR_pgf!=NULL);
}