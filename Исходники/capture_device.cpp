bool WinCaptureDevice::InitializeFirst(std::string& error)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (!SUCCEEDED(hr))
	{
		return false;
		error = "CoInitializeEx failed";
	}

	hr = MFStartup(MF_VERSION, MFSTARTUP_FULL);
	if (!SUCCEEDED(hr))
	{
		error = "MFStartup failed";
		return false;
	}

	Close();

	memset(&InputType, 0, sizeof(InputType));

	IMFActivate* activate = WinCaptureDevice::ChooseFirst(error);
	if (!activate)
		return false;

	IMFMediaSource  *pSource = NULL;
	IMFAttributes   *pAttributes = NULL;
	IMFMediaType    *pType = NULL;

	UINT32 m_cchSymbolicLink = 0;

	// Create the media source for the device.
	if (SUCCEEDED(hr))
		hr = activate->ActivateObject(__uuidof(IMFMediaSource), (void**) &pSource);

	// Get the symbolic link.
	if (SUCCEEDED(hr))
		hr = activate->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_SYMBOLIC_LINK, &SymbolicLink, &m_cchSymbolicLink);

	//
	// Create the source reader.
	//

	// Create an attribute store to hold initialization settings.

	if (SUCCEEDED(hr))
		hr = MFCreateAttributes(&pAttributes, 2);

	if (SUCCEEDED(hr))
		hr = pAttributes->SetUINT32(MF_READWRITE_DISABLE_CONVERTERS, TRUE);

	// Set the callback pointer.
	if (SUCCEEDED(hr))
		hr = pAttributes->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, this);

	if (SUCCEEDED(hr))
		hr = MFCreateSourceReaderFromMediaSource(pSource, pAttributes, &Reader);

	// Try to find a suitable input type.
	if (SUCCEEDED(hr))
	{
		for (uint i = 0; ; i++)
		{
			hr = Reader->GetNativeMediaType((DWORD) MF_SOURCE_READER_FIRST_VIDEO_STREAM, i, &pType);
			if (FAILED(hr))
			{
				error = "Failed to find a supported output format (ie RGB24)";
				break;
			}
			memset(&InputType, 0, sizeof(InputType));
			bool isTypeOK = IsMediaTypeSupported(pType, InputType);
			if (isTypeOK)
			{
				// Get the frame size.
				hr = MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &InputWidth, &InputHeight);
				// Get the image stride.
				hr = GetDefaultStride(pType, &InputDefaultStride);
				// Get the interlace mode. Default: assume progressive.
				InputInterlaceMode = (MFVideoInterlaceMode) MFGetAttributeUINT32(pType, MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
			}
			SafeRelease(&pType);
			if (isTypeOK)
				break;
		}
	}

	if (SUCCEEDED(hr))
	{
		// Ask for the first sample.
		EnableCapture = 1;
		hr = Reader->ReadSample((DWORD) MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, NULL, NULL, NULL);
	}

	if (FAILED(hr))
	{
		if (pSource)
		{
			pSource->Shutdown();
			// NOTE: The source reader shuts down the media source by default, but we might not have gotten that far.
		}
		Close();
	}

	SafeRelease(&pSource);
	SafeRelease(&pAttributes);
	SafeRelease(&pType);
	SafeRelease(&activate);

	if (FAILED(hr) && error.length() == 0)
		error = ErrorMessage(L"Failed to initialize video capture device", hr);

	return SUCCEEDED(hr);
}