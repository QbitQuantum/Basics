int select_input_mediatype(IMFTransform *transform, int in_stream_id, ADTSData adts,
						UINT8 *user_data, UINT32 user_data_len, GUID audio_format) {
	HRESULT hr = S_OK;
	IMFMediaType *t;

	// actually you can get rid of the whole block of searching and filtering mess
	// if you know the exact parameters of your media stream
	hr = MFCreateMediaType(&t);
	if (FAILED(hr))
	{
		ReportError(L"Unable to create an empty MediaType", hr);
		return -1;
	}

	// basic definition
	t->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	t->SetGUID(MF_MT_SUBTYPE, audio_format);

	// see https://docs.microsoft.com/en-us/windows/desktop/medfound/aac-decoder#example-media-types
	// and https://docs.microsoft.com/zh-cn/windows/desktop/api/mmreg/ns-mmreg-heaacwaveinfo_tag
	// for the meaning of the byte array below

	// for integrate into a larger project, it is recommended to wrap the parameters into a struct
	// and pass that struct into the function
	// const UINT8 aac_data[] = { 0x01, 0x00, 0xfe, 00, 00, 00, 00, 00, 00, 00, 00, 00, 0x11, 0x90 };
	// 0: raw aac 1: adts 2: adif 3: latm/laos
	t->SetUINT32(MF_MT_AAC_PAYLOAD_TYPE, 1);
	t->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, adts.channels);
	t->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, adts.samplerate);
	// 0xfe = 254 = "unspecified"
	t->SetUINT32(MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION, 254);
	t->SetUINT32(MF_MT_AUDIO_BLOCK_ALIGNMENT, 1);
	t->SetBlob(MF_MT_USER_DATA, user_data, user_data_len);
	hr = transform->SetInputType(in_stream_id, t, 0);
	if (FAILED(hr))
	{
		ReportError(L"failed to select input types for MFT", hr);
		return -1;
	}

	return 0;
}