HRESULT
WMFAACDecoder::SetDecoderInputType(int32_t aChannelCount,
                                   int32_t aSampleRate,
                                   BYTE* aUserData,
                                   UINT32 aUserDataLength)
{
  HRESULT hr;

  CComPtr<IMFMediaType> type;
  hr = MFCreateMediaType(&type);
  ENSURE(SUCCEEDED(hr), hr);

  hr = type->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
  ENSURE(SUCCEEDED(hr), hr);

  hr = type->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_AAC);
  ENSURE(SUCCEEDED(hr), hr);

  mRate = aSampleRate;
  hr = type->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, mRate);
  ENSURE(SUCCEEDED(hr), hr);

  mChannels = aChannelCount;
  hr = type->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, mChannels);
  ENSURE(SUCCEEDED(hr), hr);

  hr = type->SetBlob(MF_MT_USER_DATA, aUserData, aUserDataLength);
  ENSURE(SUCCEEDED(hr), hr);

  hr = mDecoder->SetInputType(0, type, 0);
  ENSURE(SUCCEEDED(hr), hr);

  return S_OK;
}