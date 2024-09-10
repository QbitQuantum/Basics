static HRESULT WINAPI AVICompressorIn_Receive(BaseInputPin *base, IMediaSample *pSample)
{
    AVICompressor *This = impl_from_BasePin(&base->pin);
    VIDEOINFOHEADER *src_videoinfo;
    REFERENCE_TIME start, stop;
    IMediaSample *out_sample;
    AM_MEDIA_TYPE *mt;
    IMediaSample2 *sample2;
    DWORD comp_flags = 0;
    BOOL is_preroll;
    BOOL sync_point;
    BYTE *ptr, *buf;
    DWORD res;
    HRESULT hres;

    TRACE("(%p)->(%p)\n", base, pSample);

    if(!This->hic) {
        FIXME("Driver not loaded\n");
        return E_UNEXPECTED;
    }

    hres = IMediaSample_QueryInterface(pSample, &IID_IMediaSample2, (void**)&sample2);
    if(SUCCEEDED(hres)) {
        FIXME("Use IMediaSample2\n");
        IMediaSample2_Release(sample2);
    }

    is_preroll = IMediaSample_IsPreroll(pSample) == S_OK;
    sync_point = IMediaSample_IsSyncPoint(pSample) == S_OK;

    hres = IMediaSample_GetTime(pSample, &start, &stop);
    if(FAILED(hres)) {
        WARN("GetTime failed: %08x\n", hres);
        return hres;
    }

    hres = IMediaSample_GetMediaType(pSample, &mt);
    if(FAILED(hres))
        return hres;

    hres = IMediaSample_GetPointer(pSample, &ptr);
    if(FAILED(hres)) {
        WARN("GetPointer failed: %08x\n", hres);
        return hres;
    }

    hres = BaseOutputPinImpl_GetDeliveryBuffer(This->out, &out_sample, &start, &stop, 0);
    if(FAILED(hres))
        return hres;

    hres = IMediaSample_GetPointer(out_sample, &buf);
    if(FAILED(hres))
        return hres;

    if((This->driver_flags & VIDCF_TEMPORAL) && !(This->driver_flags & VIDCF_FASTTEMPORALC))
        FIXME("Unsupported temporal compression\n");

    src_videoinfo = (VIDEOINFOHEADER*)This->in->pin.mtCurrent.pbFormat;
    This->videoinfo->bmiHeader.biSizeImage = This->max_frame_size;
    res = ICCompress(This->hic, sync_point ? ICCOMPRESS_KEYFRAME : 0, &This->videoinfo->bmiHeader, buf,
            &src_videoinfo->bmiHeader, ptr, 0, &comp_flags, This->frame_cnt, 0, 0, NULL, NULL);
    if(res != ICERR_OK) {
        WARN("ICCompress failed: %d\n", res);
        IMediaSample_Release(out_sample);
        return E_FAIL;
    }

    IMediaSample_SetActualDataLength(out_sample, This->videoinfo->bmiHeader.biSizeImage);
    IMediaSample_SetPreroll(out_sample, is_preroll);
    IMediaSample_SetSyncPoint(out_sample, (comp_flags&AVIIF_KEYFRAME) != 0);
    IMediaSample_SetDiscontinuity(out_sample, (IMediaSample_IsDiscontinuity(pSample) == S_OK));

    if (IMediaSample_GetMediaTime(pSample, &start, &stop) == S_OK)
        IMediaSample_SetMediaTime(out_sample, &start, &stop);
    else
        IMediaSample_SetMediaTime(out_sample, NULL, NULL);

    hres = BaseOutputPinImpl_Deliver(This->out, out_sample);
    if(FAILED(hres))
        WARN("Deliver failed: %08x\n", hres);

    IMediaSample_Release(out_sample);
    This->frame_cnt++;
    return hres;
}