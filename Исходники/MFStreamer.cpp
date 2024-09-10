HRESULT InitMFStreamer()
{
	printf("InitMFStreamer.\n");

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	CHECK_HR(InitVPXEncoder(&_vpxConfig, &_vpxCodec, WIDTH, HEIGHT), L"Failed to intialise the VPX encoder.\n");

	// Create an attribute store to hold the search criteria.
	CHECK_HR(MFCreateAttributes(&videoConfig, 1), L"Error creating video configuation.");
	//CHECK_HR(MFCreateAttributes(&audioConfig, 1), L"Error creating audio configuation.");;

	// Request video capture devices.
	CHECK_HR(videoConfig->SetGUID(
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID), L"Error initialising video configuration object.");

	// Request audio capture devices.
	/*CHECK_HR(audioConfig->SetGUID(
	MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
	MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID), L"Error initialising audio configuration object.");*/

	// Enumerate the devices,
	CHECK_HR(MFEnumDeviceSources(videoConfig, &videoDevices, &videoDeviceCount), L"Error enumerating video devices.");
	//CHECK_HR(MFEnumDeviceSources(audioConfig, &audioDevices, &audioDeviceCount), L"Error enumerating audio devices.");

	//printf("Video device Count: %i, Audio device count: %i.\n", videoDeviceCount, audioDeviceCount);
	printf("Video device Count: %i.\n", videoDeviceCount);

	CHECK_HR(videoDevices[0]->ActivateObject(IID_PPV_ARGS(&videoSource)), L"Error activating video device.");
	//CHECK_HR(audioDevices[0]->ActivateObject(IID_PPV_ARGS(&audioSource)), L"Error activating audio device.");

	// Initialize the Media Foundation platform.
	CHECK_HR(MFStartup(MF_VERSION), L"Error on Media Foundation startup.");

	/*WCHAR *pwszFileName = L"sample.mp4";
	IMFSinkWriter *pWriter;*/

	/*CHECK_HR(MFCreateSinkWriterFromURL(
	pwszFileName,
	NULL,
	NULL,
	&pWriter), L"Error creating mp4 sink writer.");*/

	// Create the source readers.
	CHECK_HR(MFCreateSourceReaderFromMediaSource(
		videoSource,
		videoConfig,
		&videoReader), L"Error creating video source reader.");

	//ListModes(videoReader);

	/*CHECK_HR(MFCreateSourceReaderFromMediaSource(
	audioSource,
	audioConfig,
	&audioReader), L"Error creating audio source reader.");*/

	FindVideoMode(videoReader, MF_INPUT_FORMAT, WIDTH, HEIGHT, desiredInputVideoType);

	if (desiredInputVideoType == NULL) {
		printf("The specified media type could not be found for the MF video reader.\n");
	}
	else {
		CHECK_HR(videoReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM, NULL, desiredInputVideoType),
			L"Error setting video reader media type.\n");

		CHECK_HR(videoReader->GetCurrentMediaType(
			(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
			&videoType), L"Error retrieving current media type from first video stream.");
		CMediaTypeTrace *videoTypeMediaTrace = new CMediaTypeTrace(videoType);

		printf("Video input media type: %s.\n", videoTypeMediaTrace->GetString());

		LONG pStride = 0;
		GetDefaultStride(videoType, &pStride);
		printf("Stride %i.\n", pStride);
			
		/*printf("Press any key to continue...");
		getchar();*/

		/*audioReader->GetCurrentMediaType(
		(DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
		&audioType);*/
		//CMediaTypeTrace *audioTypeMediaTrace = new CMediaTypeTrace(audioType);
		//printf("Audio input media type: %s.\n", audioTypeMediaTrace->GetString());

		//printf("Configuring H.264 sink.\n");

		// Set up the H.264 sink.
		/*CHECK_HR(ConfigureEncoder(videoType, &videoStreamIndex, &audioStreamIndex, pWriter), L"Error configuring encoder.");
		printf("Video stream index %i, audio stream index %i.\n", videoStreamIndex, audioStreamIndex);*/

		// Register the color converter DSP for this process, in the video 
		// processor category. This will enable the sink writer to enumerate
		// the color converter when the sink writer attempts to match the
		// media types.
		CHECK_HR(MFTRegisterLocalByCLSID(
			__uuidof(CColorConvertDMO),
			MFT_CATEGORY_VIDEO_PROCESSOR,
			L"",
			MFT_ENUM_FLAG_SYNCMFT,
			0,
			NULL,
			0,
			NULL
			), L"Error registering colour converter DSP.");

		// Add the input types to the H.264 sink writer.
		/*CHECK_HR(pWriter->SetInputMediaType(videoStreamIndex, videoType, NULL), L"Error setting the sink writer video input type.");
		videoType->Release();
		CHECK_HR(pWriter->SetInputMediaType(audioStreamIndex, audioType, NULL), L"Error setting the sink writer audio input type.");
		audioType->Release();*/

		//CHECK_HR(pWriter->BeginWriting(), L"Failed to begin writing on the H.264 sink.");

		//InitializeCriticalSection(&critsec);
	}
}