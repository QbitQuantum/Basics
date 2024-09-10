/////////////////////////////////////////////////////////
// really open the file ! (OS dependent)
//
/////////////////////////////////////////////////////////
void pix_movieDS::realOpen(char *filename)
{
	WCHAR			WideFileName[MAXPDSTRING];
	HRESULT			RetVal;
	AM_MEDIA_TYPE	MediaType;
	BOOL			bFrameTime	= TRUE;
	GUID			Guid;

	// Convert c-string to Wide string.
	memset(&WideFileName, 0, MAXPDSTRING * 2);

	if (0 == MultiByteToWideChar(CP_ACP, 0, filename, strlen(filename), WideFileName,
		MAXPDSTRING))
	{
		error("Unable to load %s", filename);

		return;
	}

	// Add a file source filter to the filter graph.
	RetVal	= FilterGraph->AddSourceFilter(WideFileName, L"SOURCE", &VideoFilter);

	if (RetVal != S_OK || NULL == VideoFilter)
	{
		error("Unable to render %s", filename);

		return;
	}

	// Create an instance of the sample grabber filter. The filter allows frames to be
	// buffered from a video source.
	RetVal	= CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)&SampleFilter);

	if (RetVal != S_OK || NULL == SampleFilter)
	{
		error("Unable to create SampleFilter interface %d", RetVal);

		return;
	}

 	// Add sample grabber filter to the filter graph.
	RetVal	= FilterGraph->AddFilter(SampleFilter, L"Sample Grabber");

	if (RetVal != S_OK)
	{
		error("Unable to add SampleFilter %d", RetVal);

		return;
	}

	// Find an interface to the SampleGrabber from the SampleGrabber filter. The
	// SampleGrabber allows frames to be grabbed from the filter. SetBufferSamples(TRUE)
	// tells the SampleGrabber to buffer the frames. SetOneShot(FALSE) tells the
	// SampleGrabber to continuously grab frames.  has GetCurrentBuffer() method
	RetVal	= SampleFilter->QueryInterface(IID_ISampleGrabber, (void **)&SampleGrabber);

	if (RetVal != S_OK || NULL == SampleGrabber)
	{
		error("Unable to create SampleGrabber interface %d", RetVal);

		return;
	}

	// Set the media type that the SampleGrabber wants.
	// MEDIATYPE_Video selects only video and not interleaved audio and video
	// MEDIASUBTYPE_RGB24 is the colorspace and format to deliver frames
	// MediaType.formattype is GUID_NULLsince it is handled later to get file info
	memset(&MediaType, 0, sizeof(AM_MEDIA_TYPE));
	MediaType.majortype		= MEDIATYPE_Video;
	MediaType.subtype		= MEDIASUBTYPE_RGB24;
	MediaType.formattype	= GUID_NULL;
	RetVal					= SampleGrabber->SetMediaType(&MediaType);

	// Set the SampleGrabber to return continuous frames
	RetVal	= SampleGrabber->SetOneShot(FALSE);

	if (RetVal != S_OK)
	{
		error("Unable to setup sample grabber %d", RetVal);

		return;
	}

	// Set the SampleGrabber to copy the data to a buffer. This only set to FALSE when a
	// callback is used.
	RetVal	= SampleGrabber->SetBufferSamples(TRUE);

	if (RetVal != S_OK)
	{
		error("Unable to setup sample grabber %d", RetVal);

		return;
	}

	// Create the Null Renderer interface. The Null Renderer is used to disable rendering of a
	// video stream to a window.
	RetVal	= CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)&NullFilter);

	if (RetVal != S_OK || NULL == NullFilter)
	{
		error("Unable to create NullFilter interface %d", RetVal);

		return;
	}

	// Add the Null Renderer filter to the FilterGraph
	RetVal	= FilterGraph->AddFilter(NullFilter, L"NullRenderer");

	if (RetVal != S_OK)
	{
		error("Unable to add NullFilter %d", RetVal);

		return;
	}

	// DS filter chain is FileSource -> SampleGrabber -> NullRenderer
	// DS can put any neeeded filters in the chain for format or colorspace conversion
	// decompression or other transforms

	// Connect the SampleFilter to the VideoFilter
	RetVal	= movieConnectFilters(FilterGraph, VideoFilter, SampleFilter);

	if (RetVal != S_OK)
	{
		error("Unable to connect filters %d", RetVal);

		return;
	}

	// Connect the NullFilter to the SampleFilter
	RetVal	= movieConnectFilters(FilterGraph, SampleFilter, NullFilter);

	if (RetVal != S_OK)
	{
		error("Unable to connect filters %d", RetVal);

		return;
	}

	// Set the time format to frames
	Guid	= TIME_FORMAT_FRAME;

	RetVal	= MediaSeeking->SetTimeFormat(&Guid);

	if (RetVal != S_OK)
	{
		// If frame time format not available, default to 100 nanosecond increments.
		bFrameTime	= FALSE;

		Guid	= TIME_FORMAT_MEDIA_TIME;

		RetVal	= MediaSeeking->SetTimeFormat(&Guid);

		if (RetVal != S_OK)
		{
			error("Unable to set video time format %d", RetVal);

			return;
		}
	}

	// Get the duration of the video. Format will be in previously set time format. This is
	// compatible with the value returned from GetCurrentPosition
	RetVal	= MediaSeeking->GetDuration(&m_Duration);

	if (RetVal != S_OK)
	{
		error("Unable to get video duration %d", RetVal);

		return;
	}

	// Set the number of frames based on the time format used.
	if (TRUE == bFrameTime)
	{
		m_numFrames	= m_Duration;
	}

	else
	{
		LONGLONG	OutFormat;
		GUID		OutGuid;

		OutGuid	= TIME_FORMAT_FRAME;
		Guid	= TIME_FORMAT_MEDIA_TIME;

		//converts from 100 nanosecond format to number of frames
		MediaSeeking->ConvertTimeFormat(&OutFormat, &OutGuid, m_Duration, &Guid);

		m_numFrames	= OutFormat;
	}

	// Get the format of the connected media.
	RetVal	= SampleGrabber->GetConnectedMediaType(&MediaType);

	if (RetVal != S_OK)
	{
		error("Unable to get media type %d", RetVal);

		return;
	}

	// The SampleGrabber will only return video of the the 'FORMAT_VideoInfo' type.
	if (FORMAT_VideoInfo == MediaType.formattype && MediaType.pbFormat != NULL)
	{
		// Format returned is specific to the formattype.
		VIDEOINFOHEADER	*VideoInfo	= (VIDEOINFOHEADER *)MediaType.pbFormat;

		// Get size of the image from the BitmapInfoHeader returned in the VIDEOINFOHEADER.
		m_xsize		= VideoInfo->bmiHeader.biWidth;
		m_ysize		= VideoInfo->bmiHeader.biHeight;
		m_csize		= 3;
	}

	else
	{
		error("Invalid media type returned %s", filename);

		return;
	}

	// Allocate video buffer if valid sizes returned.
	if (m_xsize > 0 && m_ysize > 0 && m_csize > 0)
	{
		if (m_frame != NULL)
		{
			delete [] m_frame;
		}

		m_frame		= new BYTE[m_xsize * m_ysize * m_csize];

		if (NULL == m_frame)
		{
			error("Unable to allocate memory for the video buffer %s", filename);

			return;
		}
	}

	// Release the MediaType.pbFormat data
	FreeMediaType(MediaType);

	IBaseFilter	*DVFilter;

	// If DV video is used, set the quality to 720 x 480.
	RetVal	= FilterGraph->FindFilterByName(L"DV Video Decoder", &DVFilter);

	if (S_OK == RetVal && DVFilter != NULL)
	{
		IIPDVDec	*IPDVDec;

		// Find the IIPDVDec interface
		RetVal	= DVFilter->QueryInterface(IID_IIPDVDec, (void **)&IPDVDec);

		if (S_OK == RetVal && IPDVDec != NULL)
		{
			// Set the property to DVRESOLUTION_FULL
			IPDVDec->put_IPDisplay(DVRESOLUTION_FULL);

			// Release the interface
			IPDVDec->Release();
		}

		// Release the interface
		DVFilter->Release();
	}

	post("xsize %d ysize %d csize %",m_xsize, m_ysize, m_csize);

	// Setup the pixBlock data based on the media type.
	// this is a guess at the fast past for pixels on Windows
	m_pixBlock.image.xsize	= m_xsize;
	m_pixBlock.image.ysize	= m_ysize;
	m_pixBlock.image.csize	= m_csize;
	m_pixBlock.image.format	= GL_BGR_EXT;
	m_pixBlock.image.type	= GL_UNSIGNED_BYTE;

	// Start the video stream
	RetVal	= MediaControl->Run();

	if (RetVal != S_OK && RetVal != S_FALSE)
	{
		error("Unable to start video %d", RetVal);

		return;
	}

	// Wait for the video to begin playing.
	while (TRUE)
	{
		OAFilterState	FilterState;

		// Get the state and ensure it's not in an intermediate state
		RetVal	= MediaControl->GetState(0, &FilterState);

		if (RetVal != S_OK && RetVal != VFW_S_STATE_INTERMEDIATE)
		{
			error("Unable to run video %d", RetVal);

			return;
		}

		// Ensure the video is running
		else if (RetVal == S_OK && State_Running == FilterState)
		{
			break;
		}
	}

	// Sets the tex coords
	prepareTexture();

	// Set the last frame to -1 so it will show the first frame.
	m_LastFrame	= -1;

	m_haveMovie	= TRUE;
}