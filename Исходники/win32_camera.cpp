camera_t * camera_open(const char *portname, int highres)
{
	camera_internal_t *camera = (camera_internal_t*)malloc(sizeof(camera_internal_t));
	camera->reader = NULL;

	if (highres)
	{
		console_printf("camera: highres is not supported on windows (yet).\n");
		highres = 0;
	}

	HRESULT hr = S_OK;

	// Initialize Media Foundation
	if (SUCCEEDED(hr))
	{
		hr = MFStartup(MF_VERSION);
	}
	///////////////////////////////////////////
	IMFAttributes *pAttributes = NULL;
	UINT32 m_cDevices = 0;
	IMFActivate **m_ppDevices = NULL;

	// Initialize an attribute store. We will use this to
	// specify the enumeration parameters.

	hr = MFCreateAttributes(&pAttributes, 1);

	// Ask for source type = video capture devices
	if (SUCCEEDED(hr))
	{
		hr = pAttributes->SetGUID(
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
			);
	}

	// Enumerate devices.
	if (SUCCEEDED(hr))
	{
		hr = MFEnumDeviceSources(pAttributes, &m_ppDevices, &m_cDevices);
	}

	SafeRelease(&pAttributes);

	/////////////////////////////////////////////////
	IMFActivate *pActivate = NULL;
	if (m_cDevices)
	{
		console_printf("camera: there are %d camera devices connected (0..%d).\n", m_cDevices, m_cDevices > 0 ? m_cDevices - 1 : 0);
		int device = strtol(portname, 0, 10);
		if (device < 0 || device >= m_cDevices)
			console_printf("camera: device %d does not exist.\n", device);
		else
			pActivate = m_ppDevices[device];
	}
	else
	{
		console_printf("camera: could not find a device\n");
	}
	/////////////////////////////////////////////////

	IMFMediaSource *pSource = NULL;

	//EnterCriticalSection(&m_critsec);

	// Create the media source for the device.
	hr = pActivate->ActivateObject(
		__uuidof(IMFMediaSource),
		(void**)&pSource
		);
	///////////////////////////////////////////

	//IMFAttributes *pAttributes = NULL;

	/*hr = MFCreateAttributes(&pAttributes, 2);

	if (SUCCEEDED(hr))
	{
	hr = pAttributes->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, this);
	}*/

	if (SUCCEEDED(hr))
	{
		hr = MFCreateSourceReaderFromMediaSource(
			pSource,
			NULL,//pAttributes,
			&camera->reader
			);
	}

	//SafeRelease(&pAttributes);

	////////////////////////////////////////////////////
	// The list of acceptable types.
	GUID subtypes[] = {
		MFVideoFormat_NV12, MFVideoFormat_YUY2, MFVideoFormat_UYVY,
		MFVideoFormat_RGB32, MFVideoFormat_RGB24, MFVideoFormat_IYUV
	};

	//HRESULT hr = S_OK;
	BOOL bUseNativeType = FALSE;

	GUID subtype = { 0 };

	IMFMediaType *pType = NULL;

	UINT32 width = 0, height = 0;
	int selectedSubtype = -1;

	// If the source's native format matches any of the formats in
	// the list, prefer the native format.

	// Note: The camera might support multiple output formats,
	// including a range of frame dimensions. The application could
	// provide a list to the user and have the user select the
	// camera's output format. That is outside the scope of this
	// sample, however.

	DWORD selectedStreamIndex = MF_SOURCE_READER_FIRST_VIDEO_STREAM;

	//while (true)
	//{
		hr = camera->reader->GetNativeMediaType(
			selectedStreamIndex,
			0,  // Type index
			&pType
			);

		if (FAILED(hr)) { console_printf("camera: could not get media type\n"); goto done; }

		hr = ::MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &width, &height);

		if (FAILED(hr)) { console_printf("camera: could not get resolution\n"); goto done; }

		//if (width != 1280 || height != 960)
		//{
			console_printf("camera: found resolution %dx%d\n", width, height);
			//selectedStreamIndex++;
			//continue;
		//}

		camera->size.width = width;
		camera->size.height = height;
		//break;
	//}


	/*UINT32 num = 0, denom = 0;
	hr = ::MFGetAttributeRatio(pType, MF_MT_FRAME_RATE_RANGE_MAX, &num, &denom);

	if (FAILED(hr)) { goto done; }*/

	//hr = ::MFSetAttributeSize(pType, MF_MT_FRAME_SIZE, 1280, 960);

	//if (FAILED(hr)) { goto done; }

	/*hr = ::MFSetAttributeRatio(pType, MF_MT_FRAME_RATE, num, denom);

	if (FAILED(hr)) { goto done; }*/

	hr = pType->GetGUID(MF_MT_SUBTYPE, &subtype);

	if (FAILED(hr)) { console_printf("camera: could not get stream type(1)\n"); goto done; }

	for (UINT32 i = 0; i < ARRAYSIZE(subtypes); i++)
	{
		if (subtype == subtypes[i])
		{
			hr = camera->reader->SetCurrentMediaType(
				(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
				NULL,
				pType
				);

			bUseNativeType = TRUE;
			selectedSubtype = i;
			break;
		}
	}

	if (!bUseNativeType)
	{
		// None of the native types worked. The camera might offer
		// output a compressed type such as MJPEG or DV.

		// Try adding a decoder.

		for (UINT32 i = 0; i < ARRAYSIZE(subtypes); i++)
		{
			hr = pType->SetGUID(MF_MT_SUBTYPE, subtypes[i]);

			if (FAILED(hr)) { console_printf("camera: could not get stream type(2)\n"); goto done; }

			hr = camera->reader->SetCurrentMediaType(
				(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
				NULL,
				pType
				);

			if (SUCCEEDED(hr))
			{
				selectedSubtype = i;
				break;
			}
		}
	}

/*	hr = ::MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &width, &height);
	WIDTH = width;
	HEIGHT = height;*/

	if (FAILED(hr)) { console_printf("camera: could not find stream type\n"); goto done; }

done:
	SafeRelease(&pType);

	console_printf("camera: selected type: %d, native: %s, resolution: %dx%d\n",
		selectedSubtype, bUseNativeType ? "yes" : "no", camera->size.width, camera->size.height);

	///////////////////////////////////////
	/*if (SUCCEEDED(hr))
	{
	hr = camera->reader->GetCurrentMediaType(
	(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
	&pType
	);
	}

	if (SUCCEEDED(hr))
	{
	// Register the color converter DSP for this process, in the video
	// processor category. This will enable the sink writer to enumerate
	// the color converter when the sink writer attempts to match the
	// media types.

	hr = MFTRegisterLocalByCLSID(
	__uuidof(CColorConvertDMO),
	MFT_CATEGORY_VIDEO_PROCESSOR,
	L"",
	MFT_ENUM_FLAG_SYNCMFT,
	0,
	NULL,
	0,
	NULL
	);
	}*/

	/////////////////////////////////////////////////

/*	IMFSample *pSample = NULL;
	DWORD streamIndex = 0, flags = 0;
	LONGLONG llTimeStamp = 0;

	hr = camera->reader->ReadSample(
		(DWORD)MF_SOURCE_READER_ANY_STREAM,    // Stream index.
		0,                              // Flags.
		&streamIndex,                   // Receives the actual stream index.
		&flags,                         // Receives status flags.
		&llTimeStamp,                   // Receives the time stamp.
		&pSample                        // Receives the sample or NULL.
		);*/

	if (selectedSubtype != 4)
	{
		console_printf("camera: unexpected stream type.\n");
		SafeRelease(&camera->reader);
		free(camera);
		return 0;
	}
	return (camera_t*)camera;
}