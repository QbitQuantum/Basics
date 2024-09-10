static HRESULT
CreateAudioMediaType(const WWMFPcmFormat &fmt, IMFMediaType** ppMediaType)
{
    HRESULT hr;
    IMFMediaType *pMediaType = NULL;
    *ppMediaType = NULL;

    HRG(MFCreateMediaType(&pMediaType) );
    HRG(pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio));
    HRG(pMediaType->SetGUID(MF_MT_SUBTYPE,
            (fmt.sampleFormat == WWMFBitFormatInt) ? MFAudioFormat_PCM : MFAudioFormat_Float));
    HRG(pMediaType->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS,         fmt.nChannels));
    HRG(pMediaType->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND,   fmt.sampleRate));
    HRG(pMediaType->SetUINT32(MF_MT_AUDIO_BLOCK_ALIGNMENT,      fmt.FrameBytes()));
    HRG(pMediaType->SetUINT32(MF_MT_AUDIO_AVG_BYTES_PER_SECOND, fmt.BytesPerSec()));
    HRG(pMediaType->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE,      fmt.bits));
    HRG(pMediaType->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT,    TRUE));
    if (0 != fmt.dwChannelMask) {
        HRG(pMediaType->SetUINT32(MF_MT_AUDIO_CHANNEL_MASK, fmt.dwChannelMask));
    }
    if (fmt.bits != fmt.validBitsPerSample) {
        HRG(pMediaType->SetUINT32(MF_MT_AUDIO_VALID_BITS_PER_SAMPLE, fmt.validBitsPerSample));
    }

    *ppMediaType = pMediaType;
    pMediaType = NULL; //< prevent release

end:
    SafeRelease(&pMediaType);
    return hr;
}