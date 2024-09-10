void MediaSource::LoadMetadataFromSource()
{
  IMFMetadataProvider* mfMetadataProvider = nullptr;
  IMFMetadata* mfMetadata = nullptr;
  PROPVARIANT metadataKeys, metadataValue;
  PWSTR *metadataPropertyKeys = nullptr;
  HRESULT hr;

  _metadataPropertyCount = 0;
  PropVariantInit(&metadataKeys);
  PropVariantInit(&metadataValue);

  do
  {
    if (!SUCCEEDED(hr = MFGetService(_mfMediaSource, MF_METADATA_PROVIDER_SERVICE, IID_PPV_ARGS(&mfMetadataProvider))))
    {
      // Can't get the metadata provider service for this media source, but that's ok... we'll just skip reading metadata
      hr = S_OK;
      break;
    }

    if (!SUCCEEDED(hr = mfMetadataProvider->GetMFMetadata(_mfPresentationDescriptor, 0, 0, &mfMetadata)))
      break;

    if (!SUCCEEDED(hr = mfMetadata->GetAllPropertyNames(&metadataKeys)))
      break;

    if (!SUCCEEDED(hr = PropVariantToStringVectorAlloc(metadataKeys, &metadataPropertyKeys, &_metadataPropertyCount)))
      break;

    _metadata = (MetadataKeyValuePair *)malloc(_metadataPropertyCount * sizeof(MetadataKeyValuePair));

    for (ULONG i = 0; i < _metadataPropertyCount; i++)
    {
      PWSTR metadataKey = *(metadataPropertyKeys + i);

      if (!SUCCEEDED(hr = mfMetadata->GetProperty(metadataKey, &metadataValue)))
        break;

      (_metadata + i)->Key = metadataKey;

      if (!SUCCEEDED(hr = PropVariantToStringAlloc(metadataValue, &((_metadata + i)->Value))))
        break;

      PropVariantClear(&metadataValue);
    }

    if (FAILED(hr))
      break;

  } while (0);

  if (metadataPropertyKeys) CoTaskMemFree(metadataPropertyKeys);
  if (mfMetadata) mfMetadata->Release();
  if (mfMetadataProvider) mfMetadataProvider->Release();

  if (FAILED(hr))
  {
    throw std::exception("Error occurred reading metadata from media source");
  }
}