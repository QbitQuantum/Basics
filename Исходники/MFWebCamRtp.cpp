	bool initialise()
	{
		UINT32 videoDeviceCount = 0;
		IMFAttributes *videoConfig = NULL;
		IMFActivate **videoDevices = NULL;
		WCHAR *webcamFriendlyName;
		
		CHECK_HR(MFTRegisterLocalByCLSID(
			__uuidof(CColorConvertDMO),
			MFT_CATEGORY_VIDEO_PROCESSOR,
			L"",
			MFT_ENUM_FLAG_SYNCMFT,
			0,
			NULL,
			0,
			NULL
			), "Error registering colour converter DSP.\n");

		// Get the first available webcam.
		CHECK_HR(MFCreateAttributes(&videoConfig, 1), "Error creating video configuation.\n");

		// Request video capture devices.
		CHECK_HR(videoConfig->SetGUID(
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID), "Error initialising video configuration object.");

		CHECK_HR(MFEnumDeviceSources(videoConfig, &videoDevices, &videoDeviceCount), "Error enumerating video devices.\n");

		CHECK_HR(videoDevices[WEBCAM_DEVICE_INDEX]->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, &webcamFriendlyName, NULL), "Error retrieving vide device friendly name.\n");

		wprintf(L"First available webcam: %s\n", webcamFriendlyName);

		CHECK_HR(videoDevices[WEBCAM_DEVICE_INDEX]->ActivateObject(IID_PPV_ARGS(&videoSource)), "Error activating video device.\n");

		// Create a source reader.
		CHECK_HR(MFCreateSourceReaderFromMediaSource(
			videoSource,
			videoConfig,
			&_videoReader), "Error creating video source reader.\n");

		//ListModes(_videoReader);

		CHECK_HR(_videoReader->GetCurrentMediaType(
			(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
			&videoSourceOutputType), "Error retrieving current media type from first video stream.\n");

		Console::WriteLine(GetMediaTypeDescription(videoSourceOutputType));

		// Note the webcam needs to support this media type. The list of media types supported can be obtained using the ListTypes function in MFUtility.h.
		MFCreateMediaType(&pSrcOutMediaType);
		pSrcOutMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
		//pSrcOutMediaType->SetGUID(MF_MT_SUBTYPE, WMMEDIASUBTYPE_I420);
		pSrcOutMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB24);
		MFSetAttributeSize(pSrcOutMediaType, MF_MT_FRAME_SIZE, CAMERA_RESOLUTION_WIDTH, CAMERA_RESOLUTION_HEIGHT);
		CHECK_HR(MFSetAttributeRatio(pSrcOutMediaType, MF_MT_FRAME_RATE, TARGET_FRAME_RATE, 1), "Failed to set frame rate on video device out type.\n");

		CHECK_HR(_videoReader->SetCurrentMediaType(0, NULL, pSrcOutMediaType), "Failed to set media type on source reader.\n");
		//CHECK_HR(_videoReader->SetCurrentMediaType(0, NULL, videoSourceOutputType), "Failed to setdefault  media type on source reader.\n");

		// Create H.264 encoder.
		CHECK_HR(CoCreateInstance(CLSID_CMSH264EncoderMFT, NULL, CLSCTX_INPROC_SERVER,
			IID_IUnknown, (void**)&spTransformUnk), "Failed to create H264 encoder MFT.\n");

		CHECK_HR(spTransformUnk->QueryInterface(IID_PPV_ARGS(&_pTransform)), "Failed to get IMFTransform interface from H264 encoder MFT object.\n");

		MFCreateMediaType(&pMFTOutputMediaType);
		pMFTOutputMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
		pMFTOutputMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
		//pMFTOutputMediaType->SetUINT32(MF_MT_AVG_BITRATE, 240000);
		CHECK_HR(pMFTOutputMediaType->SetUINT32(MF_MT_AVG_BITRATE, TARGET_AVERAGE_BIT_RATE), "Failed to set average bit rate on H264 output media type.\n");
		CHECK_HR(MFSetAttributeSize(pMFTOutputMediaType, MF_MT_FRAME_SIZE, CAMERA_RESOLUTION_WIDTH, CAMERA_RESOLUTION_HEIGHT), "Failed to set frame size on H264 MFT out type.\n");
		CHECK_HR(MFSetAttributeRatio(pMFTOutputMediaType, MF_MT_FRAME_RATE, TARGET_FRAME_RATE, 1), "Failed to set frame rate on H264 MFT out type.\n");
		CHECK_HR(MFSetAttributeRatio(pMFTOutputMediaType, MF_MT_PIXEL_ASPECT_RATIO, 1, 1), "Failed to set aspect ratio on H264 MFT out type.\n");
		pMFTOutputMediaType->SetUINT32(MF_MT_INTERLACE_MODE, 2);	// 2 = Progressive scan, i.e. non-interlaced.
		pMFTOutputMediaType->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT, TRUE);
		//CHECK_HR(MFSetAttributeRatio(pMFTOutputMediaType, MF_MT_MPEG2_PROFILE, eAVEncH264VProfile_Base), "Failed to set profile on H264 MFT out type.\n");
		//CHECK_HR(pMFTOutputMediaType->SetDouble(MF_MT_MPEG2_LEVEL, 3.1), "Failed to set level on H264 MFT out type.\n");
		//CHECK_HR(pMFTOutputMediaType->SetUINT32(MF_MT_MAX_KEYFRAME_SPACING, 10), "Failed to set key frame interval on H264 MFT out type.\n");
		//CHECK_HR(pMFTOutputMediaType->SetUINT32(CODECAPI_AVEncCommonQuality, 100), "Failed to set H264 codec qulaity.\n");
		//hr = pAttributes->SetUINT32(CODECAPI_AVEncMPVGOPSize, 1)

		CHECK_HR(_pTransform->SetOutputType(0, pMFTOutputMediaType, 0), "Failed to set output media type on H.264 encoder MFT.\n");

		MFCreateMediaType(&pMFTInputMediaType);
		pMFTInputMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
		pMFTInputMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_IYUV);
		CHECK_HR(MFSetAttributeSize(pMFTInputMediaType, MF_MT_FRAME_SIZE, CAMERA_RESOLUTION_WIDTH, CAMERA_RESOLUTION_HEIGHT), "Failed to set frame size on H264 MFT out type.\n");
		CHECK_HR(MFSetAttributeRatio(pMFTInputMediaType, MF_MT_FRAME_RATE, TARGET_FRAME_RATE, 1), "Failed to set frame rate on H264 MFT out type.\n");
		CHECK_HR(MFSetAttributeRatio(pMFTInputMediaType, MF_MT_PIXEL_ASPECT_RATIO, 1, 1), "Failed to set aspect ratio on H264 MFT out type.\n");
		pMFTInputMediaType->SetUINT32(MF_MT_INTERLACE_MODE, 2);

		CHECK_HR(_pTransform->SetInputType(0, pMFTInputMediaType, 0), "Failed to set input media type on H.264 encoder MFT.\n");

		CHECK_HR(_pTransform->GetInputStatus(0, &mftStatus), "Failed to get input status from H.264 MFT.\n");
		if (MFT_INPUT_STATUS_ACCEPT_DATA != mftStatus) {
			printf("E: ApplyTransform() pTransform->GetInputStatus() not accept data.\n");
			goto done;
		}

		//Console::WriteLine(GetMediaTypeDescription(pMFTOutputMediaType));

		CHECK_HR(_pTransform->ProcessMessage(MFT_MESSAGE_COMMAND_FLUSH, NULL), "Failed to process FLUSH command on H.264 MFT.\n");
		CHECK_HR(_pTransform->ProcessMessage(MFT_MESSAGE_NOTIFY_BEGIN_STREAMING, NULL), "Failed to process BEGIN_STREAMING command on H.264 MFT.\n");
		CHECK_HR(_pTransform->ProcessMessage(MFT_MESSAGE_NOTIFY_START_OF_STREAM, NULL), "Failed to process START_OF_STREAM command on H.264 MFT.\n");

		memset(&_outputDataBuffer, 0, sizeof _outputDataBuffer);

		return true;

	done:

		printf("MediaFoundationH264LiveSource initialisation failed.\n");
		return false;
	}