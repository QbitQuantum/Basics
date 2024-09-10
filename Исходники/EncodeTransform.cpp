HRESULT EncodeTransform::SetInputMediaType() 
{
	if (!mpEncoder)
	{
		return MF_E_NOT_INITIALIZED;
	}

	IMFMediaType* pMediaTypeIn = NULL;
	HRESULT hr = MFCreateMediaType(&pMediaTypeIn);
	// Set the input media type.
	if (SUCCEEDED(hr))
	{
		hr = pMediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	}
	if (SUCCEEDED(hr))
	{
		hr = pMediaTypeIn->SetGUID(MF_MT_SUBTYPE, cVideoInputFormat);
	}
	if (SUCCEEDED(hr))
	{
		hr = pMediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
	}
	if (SUCCEEDED(hr))
	{
		hr = MFSetAttributeSize(pMediaTypeIn, MF_MT_FRAME_SIZE, mStreamWidth, mStreamHeight);
	}
	if (SUCCEEDED(hr))
	{
		hr = MFSetAttributeRatio(pMediaTypeIn, MF_MT_FRAME_RATE, VIDEO_FPS, 1);
	}
	if (SUCCEEDED(hr))
	{
		hr = MFSetAttributeRatio(pMediaTypeIn, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
	}
	if (SUCCEEDED(hr))
	{
		hr = mpEncoder->SetInputType(0, pMediaTypeIn, 0); //
		if (hr == MF_E_TRANSFORM_TYPE_NOT_SET)
		{
			std::cout << "MF_E_TRANSFORM_TYPE_NOT_SET -> 0xC00D6D60L: You must set the output type first" << std::endl;
		}
		if (hr == MF_E_INVALIDMEDIATYPE)
		{
			std::cout << "MF_E_INVALIDMEDIATYPE -> 0xc00d36b4: the data specified for the media type is invalid, inconsistent, or not supported by this object" << std::endl;
		}

#if defined(CODECAPI_AVLowLatencyMode) // Win8 only
		hr = mpEncoder->QueryInterface(IID_PPV_ARGS(&mpCodecAPI));
		if (SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_UI4;
			var.ulVal = eAVEncCommonRateControlMode_Quality;
			hr = mpCodecAPI->SetValue(&CODECAPI_AVEncCommonRateControlMode, &var);
			if (FAILED(hr)){printf("Failed to set rate control mode.\n");}

			var.vt = VT_BOOL;
			var.boolVal = VARIANT_TRUE;
			hr = mpCodecAPI->SetValue(&CODECAPI_AVLowLatencyMode, &var);
			if (FAILED(hr)){ printf("Failed to enable low latency mode.\n"); }

			// This property controls the quality level when the encoder is not using a constrained bit rate. The AVEncCommonRateControlMode property determines whether the bit rate is constrained.
			VARIANT quality;
			InitVariantFromUInt32(50, &quality);
			hr = mpCodecAPI->SetValue(&CODECAPI_AVEncCommonQuality, &quality);
			if (FAILED(hr)){ printf("Failed to adjust quality mode.\n"); }
		}
#endif
	}

	return hr;
}