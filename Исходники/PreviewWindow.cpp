// Called by the DecoderMF class when the media type
// changes.
//
// Thread context: decoder thread
bool PreviewWindow::SetMediaType(IMFMediaType* mediaType)
{
	HRESULT			hr;
	bool			ret = false;
	GUID			subtype;
	UINT			width, height;
	LONG			defaultStride;
	MFRatio			PAR = { 0 };

	EnterCriticalSection(&m_criticalSection);

		hr = mediaType->GetGUID(MF_MT_SUBTYPE, &subtype);
		if (FAILED(hr))
			goto bail;

		hr = MFGetAttributeSize(mediaType, MF_MT_FRAME_SIZE, &width, &height);
		if (FAILED(hr))
			goto bail;

		// TODO: get if it's interlaced / progressive (MF_MT_INTERLACE_MODE)

		hr = GetDefaultStride(mediaType, &defaultStride);
		if (FAILED(hr))
			goto bail;

		// Get the pixel aspect ratio. Default: Assume square pixels (1:1)
		hr = MFGetAttributeRatio(mediaType, MF_MT_PIXEL_ASPECT_RATIO,
			(UINT32*)&PAR.Numerator,
			(UINT32*)&PAR.Denominator);

		if (FAILED(hr))
		{
			PAR.Numerator = PAR.Denominator = 1;
		}

		// Creates a new RGBA (32bpp) buffer for the converted frame
		m_width = width;
		m_height = height;
		m_defaultStride = defaultStride;
		m_newTextureInBuffer = false;

		ret = true;

bail:
	LeaveCriticalSection(&m_criticalSection);

	return ret;
}