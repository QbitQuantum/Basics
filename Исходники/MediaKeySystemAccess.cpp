/* static */
bool
MediaKeySystemAccess::IsSupported(const nsAString& aKeySystem,
                                  const Sequence<MediaKeySystemOptions>& aOptions)
{
  nsCOMPtr<mozIGeckoMediaPluginService> mps =
    do_GetService("@mozilla.org/gecko-media-plugin-service;1");
  if (NS_WARN_IF(!mps)) {
    return false;
  }

  for (size_t i = 0; i < aOptions.Length(); i++) {
    const MediaKeySystemOptions& options = aOptions[i];
    if (!options.mInitDataType.EqualsLiteral("cenc")) {
      continue;
    }
    if (!options.mAudioCapability.IsEmpty() ||
        !options.mVideoCapability.IsEmpty()) {
      // Don't support any capabilites until we know we have a CDM with
      // capabilities...
      continue;
    }
    if (!options.mAudioType.IsEmpty() &&
        !IsPlayableWithGMP(mps, aKeySystem, options.mAudioType)) {
      continue;
    }
    if (!options.mVideoType.IsEmpty() &&
        !IsPlayableWithGMP(mps, aKeySystem, options.mVideoType)) {
      continue;
    }

    // Our sandbox provides an origin specific unique identifier, and the
    // ability to persist data. We don't yet have a way to turn those off
    // and on for specific GMPs/CDMs, so we don't check the uniqueidentifier
    // and stateful attributes here.

    return true;
  }
  return false;
}