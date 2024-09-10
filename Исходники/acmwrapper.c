static HRESULT ACMWrapper_ProcessSampleData(TransformFilterImpl* pTransformFilter, LPBYTE data, DWORD size)
{
    ACMWrapperImpl* This = (ACMWrapperImpl*)pTransformFilter;
    AM_MEDIA_TYPE amt;
    HRESULT hr;
    IMediaSample* pSample = NULL;
    DWORD cbDstStream;
    LPBYTE pbDstStream;
    ACMSTREAMHEADER ash;
    DWORD offset = 0;
    BOOL stop = FALSE;
    BOOL unprepare_header = FALSE;
    MMRESULT res;

    TRACE("(%p)->(%p,%ld)\n", This, data, size);

    hr = IPin_ConnectionMediaType(This->tf.ppPins[0], &amt);
    if (FAILED(hr)) {
	ERR("Unable to retrieve media type\n");
	goto error;
    }

    while(!stop)
    {
	DWORD rem_buf = This->max_size - This->current_size;
	DWORD rem_smp = size - offset;
	DWORD copy_size = min(rem_buf, rem_smp);

	memcpy(This->buffer + This->current_size, data + offset, copy_size);
	This->current_size += copy_size;
	offset += copy_size;

	if (offset == size)
	    stop = TRUE;
	if (This->current_size < This->max_size)
	    break;
  
	hr = OutputPin_GetDeliveryBuffer((OutputPin*)This->tf.ppPins[1], &pSample, NULL, NULL, 0);
	if (FAILED(hr)) {
	    ERR("Unable to get delivery buffer (%lx)\n", hr);
	    goto error;
	}

	hr = IMediaSample_SetActualDataLength(pSample, 0);
	assert(hr == S_OK);

	hr = IMediaSample_GetPointer(pSample, &pbDstStream);
	if (FAILED(hr)) {
	    ERR("Unable to get pointer to buffer (%lx)\n", hr);
	    goto error;
	}
	cbDstStream = IMediaSample_GetSize(pSample);

	ash.cbStruct = sizeof(ash);
	ash.fdwStatus = 0;
	ash.dwUser = 0;
	ash.pbSrc = This->buffer;
	ash.cbSrcLength = This->current_size;
	ash.pbDst = pbDstStream;
	ash.cbDstLength = cbDstStream;

	if ((res = acmStreamPrepareHeader(This->has, &ash, 0))) {
	    ERR("Cannot prepare header %d\n", res);
	    goto error;
	}

	unprepare_header = TRUE;

	if ((res = acmStreamConvert(This->has, &ash, This->reinit_codec ? ACM_STREAMCONVERTF_START : 0))) {
	    ERR("Cannot convert data header %d\n", res);
	    goto error;
	}
	This->reinit_codec = FALSE;

	TRACE("used in %lu, used out %lu\n", ash.cbSrcLengthUsed, ash.cbDstLengthUsed);

	hr = IMediaSample_SetActualDataLength(pSample, ash.cbDstLengthUsed);
	assert(hr == S_OK);

	if (ash.cbSrcLengthUsed < ash.cbSrcLength) {
	    This->current_size = ash.cbSrcLength - ash.cbSrcLengthUsed;
	    memmove(This->buffer, This->buffer + ash.cbSrcLengthUsed, This->current_size);
	}
	else
	    This->current_size = 0;

	hr = OutputPin_SendSample((OutputPin*)This->tf.ppPins[1], pSample);
	if (hr != S_OK && hr != VFW_E_NOT_CONNECTED) {
	    ERR("Error sending sample (%lx)\n", hr);
	    goto error;
        }

error:
	if (unprepare_header && (res = acmStreamUnprepareHeader(This->has, &ash, 0)))
	    ERR("Cannot unprepare header %d\n", res);

	if (pSample)
	    IMediaSample_Release(pSample);
    }

    return hr;
}