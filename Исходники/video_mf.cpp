void MfVideoEncoder::Init(int width, int height, int fps) {
	mWidth = width;
	mHeight = height;
	mFps = fps;
	mFrameTime = 10 * 1000 * 1000 / fps;

	CComPtr<IMFMediaType> pMediaTypeOut;
	CComPtr<IMFMediaType> pMediaTypeIn;

	HRESULT hr = MFCreateSinkWriterFromURL(mFilename.c_str(), NULL, NULL, &mSinkWriter);

	// Set the output media type.
	if (SUCCEEDED(hr)) {
		hr = MFCreateMediaType(&pMediaTypeOut);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeOut->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeOut->SetUINT32(MF_MT_AVG_BITRATE, 8000000);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
	}
	if (SUCCEEDED(hr)) {
		hr = MFSetAttributeSize(pMediaTypeOut, MF_MT_FRAME_SIZE, width, height);
	}
	if (SUCCEEDED(hr)) {
		hr = MFSetAttributeRatio(pMediaTypeOut, MF_MT_FRAME_RATE, fps, 1);
	}
	if (SUCCEEDED(hr)) {
		hr = MFSetAttributeRatio(pMediaTypeOut, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
	}
	pMediaTypeOut->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT, 1);

	if (SUCCEEDED(hr)) {
		hr = mSinkWriter->AddStream(pMediaTypeOut, (DWORD*)&mStreamIndex);
	}

	// Set the input media type.
	if (SUCCEEDED(hr)) {
		hr = MFCreateMediaType(&pMediaTypeIn);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeIn->SetUINT32(MF_MT_MPEG2_PROFILE, 77);
	}
	if (SUCCEEDED(hr)) {
		hr = pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
	}
	if (SUCCEEDED(hr)) {
		hr = MFSetAttributeSize(pMediaTypeIn, MF_MT_FRAME_SIZE, width, height);
	}
	if (SUCCEEDED(hr)) {
		hr = MFSetAttributeRatio(pMediaTypeIn, MF_MT_FRAME_RATE, fps, 1);
	}
	if (SUCCEEDED(hr)) {
		hr = MFSetAttributeRatio(pMediaTypeIn, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
	}
	if (SUCCEEDED(hr)) {
		hr = mSinkWriter->SetInputMediaType(mStreamIndex, pMediaTypeIn, nullptr);
	}
	
	// Tell the sink writer to start accepting data.
	if (SUCCEEDED(hr)) {
		hr = mSinkWriter->BeginWriting();
	}
	
	CComPtr<ICodecAPI> encoder;
	hr = mSinkWriter->GetServiceForStream(0, GUID_NULL, IID_PPV_ARGS(&encoder));
	if (SUCCEEDED(hr)) {
		CComVariant quality((UINT32)eAVEncCommonRateControlMode_CBR, VT_UI4);
		hr = encoder->SetValue(&CODECAPI_AVEncCommonRateControlMode, &quality);
	}	
	if (SUCCEEDED(hr)) {
		CComVariant quality((UINT32)80000000, VT_UI4);
		hr = encoder->SetValue(&CODECAPI_AVEncCommonMeanBitRate, &quality);
	}
	
	// Return the pointer to the caller.
	if (!SUCCEEDED(hr)) {
		mSinkWriter.Release();
		throw TempleException("Unable to begin writing to the video stream");
	}
}