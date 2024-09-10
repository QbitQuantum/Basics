HRESULT HDMediaSource::FindBestVideoStreamIndex(IMFPresentationDescriptor* ppd,PDWORD pdwStreamId,UINT* width,UINT* height,float* fps)
{
	if (ppd == nullptr)
		return E_INVALIDARG;

	DWORD dwCount = 0;
	HRESULT hr = ppd->GetStreamDescriptorCount(&dwCount);
	if (FAILED(hr))
		return hr;

	int vid_count = 0;

	auto pw = std::unique_ptr<unsigned[]>(new unsigned[dwCount]);
	auto ph = std::unique_ptr<unsigned[]>(new unsigned[dwCount]);
	auto psid = std::unique_ptr<DWORD[]>(new DWORD[dwCount]);

	for (unsigned i = 0;i < dwCount;i++)
	{
		BOOL fSelected;
		ComPtr<IMFStreamDescriptor> psd;

		hr = ppd->GetStreamDescriptorByIndex(i,&fSelected,psd.GetAddressOf());
		if (FAILED(hr))
			break;

		DWORD dwStreamId = 0;
		hr = psd->GetStreamIdentifier(&dwStreamId);
		if (FAILED(hr))
			break;

		ComPtr<IMFMediaTypeHandler> pHandler;
		hr = psd->GetMediaTypeHandler(pHandler.GetAddressOf());
		if (FAILED(hr))
			return hr;

		ComPtr<IMFMediaType> pMediaType;
		hr = pHandler->GetCurrentMediaType(pMediaType.GetAddressOf());
		if (FAILED(hr))
			break;

		if (FAILED(WMF::Misc::IsVideoMediaType(pMediaType.Get())))
			continue;
		
		UINT nWidth = 0,nHeight = 0;
		hr = MFGetAttributeSize(pMediaType.Get(),MF_MT_FRAME_SIZE,&nWidth,&nHeight);
		if (FAILED(hr))
			continue;

		MFRatio fps_ratio = {0,0};
		MFGetAttributeRatio(pMediaType.Get(),MF_MT_FRAME_RATE,
			(PUINT32)&fps_ratio.Numerator,(PUINT32)&fps_ratio.Denominator);

		if (fps && fps_ratio.Denominator != 0 && fps_ratio.Numerator != 0)
			*fps = (float)fps_ratio.Numerator / (float)fps_ratio.Denominator;

		pw[vid_count] = nWidth;
		ph[vid_count] = nHeight;
		psid[vid_count] = dwStreamId;

		vid_count++;
	}

	if (FAILED(hr))
		return hr;

	if (vid_count == 0)
		return MF_E_NOT_FOUND;

	unsigned cur_wh = pw[0] + ph[0];
	int max_index = 0;

	for (int i = 0;i < vid_count;i++)
	{
		if ((pw[i] + ph[i]) > cur_wh)
		{
			cur_wh = pw[i] + ph[i];
			max_index = i;
		}
	}

	if (pdwStreamId)
		*pdwStreamId = psid[max_index];

	if (width)
		*width = pw[max_index];
	if (height)
		*height = ph[max_index];

	return S_OK;
}