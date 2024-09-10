nsresult
AppleATDecoder::GetInputAudioDescription(AudioStreamBasicDescription& aDesc,
                                         const nsTArray<uint8_t>& aExtraData)
{
  // Request the properties from CoreAudio using the codec magic cookie
  AudioFormatInfo formatInfo;
  PodZero(&formatInfo.mASBD);
  formatInfo.mASBD.mFormatID = mFormatID;
  if (mFormatID == kAudioFormatMPEG4AAC) {
    formatInfo.mASBD.mFormatFlags = mConfig.extended_profile;
  }
  formatInfo.mMagicCookieSize = aExtraData.Length();
  formatInfo.mMagicCookie = aExtraData.Elements();

  UInt32 formatListSize;
  // Attempt to retrieve the default format using
  // kAudioFormatProperty_FormatInfo method.
  // This method only retrieves the FramesPerPacket information required
  // by the decoder, which depends on the codec type and profile.
  aDesc.mFormatID = mFormatID;
  aDesc.mChannelsPerFrame = mConfig.channel_count;
  aDesc.mSampleRate = mConfig.samples_per_second;
  UInt32 inputFormatSize = sizeof(aDesc);
  OSStatus rv = AudioFormatGetProperty(kAudioFormatProperty_FormatInfo,
                                       0,
                                       NULL,
                                       &inputFormatSize,
                                       &aDesc);
  if (NS_WARN_IF(rv)) {
    return NS_ERROR_FAILURE;
  }

  // If any of the methods below fail, we will return the default format as
  // created using kAudioFormatProperty_FormatInfo above.
  rv = AudioFormatGetPropertyInfo(kAudioFormatProperty_FormatList,
                                  sizeof(formatInfo),
                                  &formatInfo,
                                  &formatListSize);
  if (rv || (formatListSize % sizeof(AudioFormatListItem))) {
    return NS_OK;
  }
  size_t listCount = formatListSize / sizeof(AudioFormatListItem);
  nsAutoArrayPtr<AudioFormatListItem> formatList(
    new AudioFormatListItem[listCount]);

  rv = AudioFormatGetProperty(kAudioFormatProperty_FormatList,
                              sizeof(formatInfo),
                              &formatInfo,
                              &formatListSize,
                              formatList);
  if (rv) {
    return NS_OK;
  }
  LOG("found %u available audio stream(s)",
      formatListSize / sizeof(AudioFormatListItem));
  // Get the index number of the first playable format.
  // This index number will be for the highest quality layer the platform
  // is capable of playing.
  UInt32 itemIndex;
  UInt32 indexSize = sizeof(itemIndex);
  rv = AudioFormatGetProperty(kAudioFormatProperty_FirstPlayableFormatFromList,
                              formatListSize,
                              formatList,
                              &indexSize,
                              &itemIndex);
  if (rv) {
    return NS_OK;
  }

  aDesc = formatList[itemIndex].mASBD;

  return NS_OK;
}