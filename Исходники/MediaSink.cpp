IMFTransform* MediaSink::GetAudioEncoderForStream(WORD streamNumber)
{
  IMFMediaType* streamMediaType = nullptr;
  IPropertyStore* encodingConfigurationProperties = nullptr;
  IMFActivate* encoderActivationObj = nullptr;
  IMFTransform* mfTransform;
  HRESULT hr;

  do
  {
    // Need to get the mediatype for the output stream in order to instatiated the 
    // encoder.  My first inclination was to get the stream sink like we did in 
    // CreateTopologyOutputNode, and that could work, but... we also need to
    // get the encoder configuration parameters, which are tacked on to the 
    // IMFMediaSinkContentInfo object.  Uggh.  The Microsoft example does a 
    // little bit of both in order to maximize confusion...

    streamMediaType = GetMediaTypeForStream(streamNumber);

    if (!SUCCEEDED(hr = _mfAsfContentInfo->GetEncodingConfigurationPropertyStore(streamNumber, &encodingConfigurationProperties)))
      break;

    if (!SUCCEEDED(hr = MFCreateWMAEncoderActivate(streamMediaType, encodingConfigurationProperties, &encoderActivationObj)))
      break;

    if (!SUCCEEDED(hr = encoderActivationObj->ActivateObject(IID_PPV_ARGS(&mfTransform))))
      break;
  } while (0);

  if (FAILED(hr))
    throw std::exception("Unable to retrieve transform for StreamSink");

  return mfTransform;
}