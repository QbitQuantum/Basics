nsresult
WMFReader::Seek(int64_t aTargetUs,
                int64_t aStartTime,
                int64_t aEndTime,
                int64_t aCurrentTime)
{
  LOG("WMFReader::Seek() %lld", aTargetUs);

  NS_ASSERTION(mDecoder->OnDecodeThread(), "Should be on decode thread.");
  if (!mCanSeek) {
    return NS_ERROR_FAILURE;
  }

  nsresult rv = ResetDecode();
  NS_ENSURE_SUCCESS(rv, rv);

  AutoPropVar var;
  HRESULT hr = InitPropVariantFromInt64(UsecsToHNs(aTargetUs), &var);
  NS_ENSURE_TRUE(SUCCEEDED(hr), NS_ERROR_FAILURE);

  hr = mSourceReader->SetCurrentPosition(GUID_NULL, var);
  NS_ENSURE_TRUE(SUCCEEDED(hr), NS_ERROR_FAILURE);

  return DecodeToTarget(aTargetUs);
}