// Called by the constructor only (for setting up the IMFTransform)
//
// Thread context: Dialog window thread
bool DecoderMF::CreateInputMediaType(IMFMediaType** mediaType)
{
	bool			ret = false;
	HRESULT			hr;
	IMFMediaType*	newMediaType = NULL;

	if (mediaType == NULL)
		return false;

	hr = MFCreateMediaType(&newMediaType);
    if (FAILED(hr))
		goto bail;

	hr = newMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	if (FAILED(hr))
		goto bail;

	hr = newMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
	if (FAILED(hr))
		goto bail;

	ret = true;

bail:
	if (ret == false)
	{
		if (newMediaType != NULL)
		{
			newMediaType->Release();
			newMediaType = NULL;
		}
	}
	else
	{
		*mediaType = newMediaType;
	}

	return ret;
}