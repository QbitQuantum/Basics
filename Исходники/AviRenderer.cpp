// --[  Method  ]---------------------------------------------------------------
//
//  - Class     : CAviRenderer
//  - prototype : bool StartRender(CWindowGL *pWindowGL, std::string strAviFile, int nFramerate)
//
//  - Purpose   : Prepares the object for capturing the opengl window to an AVI.
//
// -----------------------------------------------------------------------------
bool CAviRenderer::StartRender(CWindowGL *pWindowGL, std::string strAviFile, int nFramerate)
{
	assert(pWindowGL);

	m_pWindowGL  = NULL;
	m_bIsWorking = false;

	// Check VFW version.

	WORD wVer = HIWORD(VideoForWindowsVersion());

	if(wVer < 0x010A)
	{
		CLogger::ErrorWindow("Video For Windows outdated version");
		return false;
	}

	// Init library

	AVIFileInit();

    // Get an image and stuff it into a bitmap.

	HRESULT hr;
    HBITMAP bmp;

	if((bmp = LoadBMPFromFB(pWindowGL)) == NULL)
	{
		return false;
	}

	LPBITMAPINFOHEADER lpInfoHeader = (LPBITMAPINFOHEADER)GlobalLock(MakeDib(bmp, 32));
    DeleteObject(bmp);

	if(lpInfoHeader == NULL)
	{
		LOG.Write("\nERROR - CAviRenderer::StartRender(): GlobalLock() failed.");
		return false;
	}

	m_nWidth  = (int)lpInfoHeader->biWidth;
	m_nHeight = (int)lpInfoHeader->biHeight;

	// Open an avi file for writing

	hr = AVIFileOpen(	&m_pAviFile,		    // returned file pointer
						strAviFile.data(),		// file name
						OF_WRITE | OF_CREATE,	// mode to open file with
						NULL);					// use handler determined
												// from file extension....
	if (hr != AVIERR_OK)
	{
		LOG.Write("\nERROR - CAviRenderer::StartRender(): AVIFileOpen() failed.");
		GlobalFreePtr(lpInfoHeader);
		return false;
	}

	// Configure the stream

	_fmemset(&m_aviStreamInfo, 0, sizeof(m_aviStreamInfo));

	m_aviStreamInfo.fccType                = streamtypeVIDEO; // stream type
	m_aviStreamInfo.fccHandler             = 0;
	m_aviStreamInfo.dwScale                = 1;
	m_aviStreamInfo.dwRate                 = nFramerate;
	m_aviStreamInfo.dwSuggestedBufferSize  = lpInfoHeader->biSizeImage;

	SetRect(&m_aviStreamInfo.rcFrame, 0, 0,	// rectangle for stream
			(int)lpInfoHeader->biWidth,
			(int)lpInfoHeader->biHeight);

	// And create the stream

	hr = AVIFileCreateStream(m_pAviFile,		// file pointer
						     &m_pAviStream,		// returned stream pointer
							 &m_aviStreamInfo);	// stream header
	if(hr != AVIERR_OK)
	{
		LOG.Write("\nERROR - CAviRenderer::StartRender(): AVIFileCreateStream() failed.");
		GlobalFreePtr(lpInfoHeader);
		return false;
	}

	// Get save options (prompt dialog)

	_fmemset(&m_aviOptions, 0, sizeof(m_aviOptions));

	if(!AVISaveOptions(NULL, 0, 1, &m_pAviStream, (LPAVICOMPRESSOPTIONS FAR *) &m_pAviOptions))
	{
        LOG.Write("\nERROR - CAviRenderer::StartRender(): AVISaveOptions() failed.");
		GlobalFreePtr(lpInfoHeader);
		return false;
	}

	// Create compressed stream

	hr = AVIMakeCompressedStream(&m_pAviStreamCompressed, m_pAviStream, &m_aviOptions, NULL);

	if(hr != AVIERR_OK)
	{
        LOG.Write("\nERROR - CAviRenderer::StartRender(): AVIMakeCompressedStream() failed.");
		GlobalFreePtr(lpInfoHeader);
		return false;
	}

	// Set it's format

	hr = AVIStreamSetFormat(m_pAviStreamCompressed, 0,
							lpInfoHeader,	         // stream format
							lpInfoHeader->biSize +   // format size
							lpInfoHeader->biClrUsed * sizeof(RGBQUAD));

	if(hr != AVIERR_OK)
	{
		LOG.Write("\nERROR - CAviRenderer::StartRender(): AVIStreamSetFormat() failed.");
		GlobalFreePtr(lpInfoHeader);
		return false;
	}

	m_pWindowGL  = pWindowGL;
	m_bIsWorking = true;

	UpdateWindow(pWindowGL->GetHWND());

	return true;
}