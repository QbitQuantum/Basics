HRESULT MakeVideoOutputType(IMediaObject   *pDMO,
							AM_MEDIA_TYPE  *pmtIn,
							VideoEncParams *pParams,
							AM_MEDIA_TYPE  *pmt      )
{

	HRESULT             hr                   = S_OK;
	VIDEOINFOHEADER2    *pvih2               = NULL;
	VIDEOINFOHEADER     vih;
	IWMCodecPrivateData *pWMCodecPrivateData = NULL;
	DWORD               cbPrivateData        = 0;
	BYTE                *pbPrivateData       = NULL;
	BYTE                *pNewFormat          = NULL;

	if( NULL == pDMO    ||
		NULL == pmtIn   ||
		NULL == pParams ||
		NULL == pmt     )
	{
		return ( E_INVALIDARG );
	}

	if( NULL == pmtIn->pbFormat || pmtIn->cbFormat < sizeof( VIDEOINFOHEADER ) )
	{
		return ( E_INVALIDARG );
	}

	// make up a partial media type
	pmt->majortype            = MEDIATYPE_Video;
	pmt->formattype           = FORMAT_VideoInfo;
	pmt->bFixedSizeSamples    = FALSE;
	pmt->bTemporalCompression = TRUE;

	if( pmtIn->formattype == FORMAT_VideoInfo )
	{
		vih = *(VIDEOINFOHEADER*)pmtIn->pbFormat;
	}
	else if( pmtIn->formattype == FORMAT_VideoInfo2 )
	{
		pvih2 = (VIDEOINFOHEADER2*)pmtIn->pbFormat;
		vih.rcSource        = pvih2->rcSource;
		vih.rcTarget        = pvih2->rcTarget;
		vih.AvgTimePerFrame = pvih2->AvgTimePerFrame;
		vih.bmiHeader       = pvih2->bmiHeader;
	}
	else
		return ( E_VIDEO_INVALID_INPUT_TYPE );

	vih.dwBitRate            = (DWORD)pParams->nBitrate;
	vih.dwBitErrorRate       = 0;
	vih.bmiHeader.biPlanes   = 1;
	vih.bmiHeader.biBitCount = 24;
	pmt->subtype = WMCMEDIASUBTYPE_WMV1;
	pmt->subtype.Data1=pParams->dwTag;
	vih.bmiHeader.biCompression = pParams->dwTag;
	//
	//use the partial format above to get the private data
	//
	pmt->pbFormat = (BYTE*)CoTaskMemAlloc( sizeof( VIDEOINFOHEADER));
	memcpy( pmt->pbFormat , &vih, sizeof( VIDEOINFOHEADER));
	pmt->cbFormat = sizeof( vih );

	do
	{
		hr = pDMO->QueryInterface(IID_IWMCodecPrivateData, (void**)&pWMCodecPrivateData);
		if( FAILED( hr ) )
		{
			hr = E_NO_PRIVATE_DATA;
			break;
		}

		hr = pWMCodecPrivateData->SetPartialOutputType( pmt );
		if( FAILED( hr ) )
		{
			hr = E_PARTIAL_TYPE_REJECTED;
			break;
		}

		hr = pWMCodecPrivateData->GetPrivateData( NULL, &cbPrivateData );
		if( FAILED( hr ) )
		{
			hr = E_NO_PRIVATE_DATA_COUNT;
			break;
		}

		if( 0 == cbPrivateData )
		{ // No private data
			hr = S_OK;
			break;
		}
		pbPrivateData = new BYTE[ cbPrivateData ];
		if( pbPrivateData == NULL )
		{
			hr = E_OUTOFMEMORY;
			break;
		}
		//
		// get the private data
		//
		hr = pWMCodecPrivateData->GetPrivateData( pbPrivateData, &cbPrivateData );
		if( FAILED( hr ) )
		{
			hr = E_PRIVATE_DATA_FAILED;
			break;
		}

		//
		//modify the media type accordingly
		//
		pNewFormat = (BYTE*)CoTaskMemAlloc( sizeof( VIDEOINFOHEADER) + cbPrivateData );
		if( NULL == pNewFormat )
		{
			hr = E_OUTOFMEMORY;
			break;
		}

		memcpy( pNewFormat, pmt->pbFormat, sizeof( VIDEOINFOHEADER));
		CoTaskMemFree(pmt->pbFormat);
		memcpy( pNewFormat + sizeof( VIDEOINFOHEADER), pbPrivateData, cbPrivateData);
		pmt->pbFormat = pNewFormat;
		pmt->cbFormat = sizeof( VIDEOINFOHEADER) + cbPrivateData;
		((VIDEOINFOHEADER*)pmt->pbFormat)->bmiHeader.biSize         += cbPrivateData;
		((VIDEOINFOHEADER*)pmt->pbFormat)->bmiHeader.biClrUsed       = 0;
		((VIDEOINFOHEADER*)pmt->pbFormat)->bmiHeader.biClrImportant  = 0;
		((VIDEOINFOHEADER*)pmt->pbFormat)->bmiHeader.biXPelsPerMeter = 0;
		((VIDEOINFOHEADER*)pmt->pbFormat)->bmiHeader.biYPelsPerMeter = 0;
	}
	while( FALSE );

	SAFERELEASE( pWMCodecPrivateData );
	SAFEDELETE( pbPrivateData );

	return ( hr );
}