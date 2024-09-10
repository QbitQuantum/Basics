static int mf_decompress(H264_CONTEXT* h264, const BYTE* pSrcData, UINT32 SrcSize)
{
	HRESULT hr;
	BYTE* pbBuffer = NULL;
	DWORD cbMaxLength = 0;
	DWORD cbCurrentLength = 0;
	DWORD outputStatus = 0;
	IMFSample* inputSample = NULL;
	IMFMediaBuffer* inputBuffer = NULL;
	IMFMediaBuffer* outputBuffer = NULL;
	MFT_OUTPUT_DATA_BUFFER outputDataBuffer;
	H264_CONTEXT_MF* sys = (H264_CONTEXT_MF*) h264->pSystemData;
	INT32* iStride = h264->iStride;
	BYTE** pYUVData = h264->pYUVData;
	hr = sys->MFCreateMemoryBuffer(SrcSize, &inputBuffer);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "MFCreateMemoryBuffer failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	hr = inputBuffer->lpVtbl->Lock(inputBuffer, &pbBuffer, &cbMaxLength,
	                               &cbCurrentLength);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "Lock failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	CopyMemory(pbBuffer, pSrcData, SrcSize);
	hr = inputBuffer->lpVtbl->SetCurrentLength(inputBuffer, SrcSize);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "SetCurrentLength failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	hr = inputBuffer->lpVtbl->Unlock(inputBuffer);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "Unlock failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	hr = sys->MFCreateSample(&inputSample);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "MFCreateSample failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	inputSample->lpVtbl->AddBuffer(inputSample, inputBuffer);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "AddBuffer failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	inputBuffer->lpVtbl->Release(inputBuffer);
	hr = sys->transform->lpVtbl->ProcessInput(sys->transform, 0, inputSample, 0);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "ProcessInput failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	hr = mf_create_output_sample(sys);

	if (FAILED(hr))
	{
		WLog_ERR(TAG, "mf_create_output_sample failure: 0x%08"PRIX32"", hr);
		goto error;
	}

	outputDataBuffer.dwStreamID = 0;
	outputDataBuffer.dwStatus = 0;
	outputDataBuffer.pEvents = NULL;
	outputDataBuffer.pSample = sys->outputSample;
	hr = sys->transform->lpVtbl->ProcessOutput(sys->transform, 0, 1,
	        &outputDataBuffer, &outputStatus);

	if (hr == MF_E_TRANSFORM_STREAM_CHANGE)
	{
		UINT32 stride = 0;
		UINT64 frameSize = 0;

		if (sys->outputType)
		{
			sys->outputType->lpVtbl->Release(sys->outputType);
			sys->outputType = NULL;
		}

		hr = mf_find_output_type(sys, &MFVideoFormat_IYUV, &sys->outputType);

		if (FAILED(hr))
		{
			WLog_ERR(TAG, "mf_find_output_type failure: 0x%08"PRIX32"", hr);
			goto error;
		}

		hr = sys->transform->lpVtbl->SetOutputType(sys->transform, 0, sys->outputType,
		        0);

		if (FAILED(hr))
		{
			WLog_ERR(TAG, "SetOutputType failure: 0x%08"PRIX32"", hr);
			goto error;
		}

		hr = mf_create_output_sample(sys);

		if (FAILED(hr))
		{
			WLog_ERR(TAG, "mf_create_output_sample failure: 0x%08"PRIX32"", hr);
			goto error;
		}

		hr = sys->outputType->lpVtbl->GetUINT64(sys->outputType, &MF_MT_FRAME_SIZE,
		                                        &frameSize);

		if (FAILED(hr))
		{
			WLog_ERR(TAG, "GetUINT64(MF_MT_FRAME_SIZE) failure: 0x%08"PRIX32"", hr);
			goto error;
		}

		sys->frameWidth = (UINT32)(frameSize >> 32);
		sys->frameHeight = (UINT32) frameSize;
		hr = sys->outputType->lpVtbl->GetUINT32(sys->outputType, &MF_MT_DEFAULT_STRIDE,
		                                        &stride);

		if (FAILED(hr))
		{
			WLog_ERR(TAG, "GetUINT32(MF_MT_DEFAULT_STRIDE) failure: 0x%08"PRIX32"", hr);
			goto error;
		}

		if (!avc420_ensure_buffer(h264, stride, sys->frameWidth, sys->frameHeight))
			goto error;
	}