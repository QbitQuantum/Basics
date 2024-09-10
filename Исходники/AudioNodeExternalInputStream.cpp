static void
CopyChunkToBlock(AudioChunk& aInput, AudioBlock *aBlock,
                 uint32_t aOffsetInBlock)
{
  uint32_t blockChannels = aBlock->ChannelCount();
  AutoTArray<const T*,2> channels;
  if (aInput.IsNull()) {
    channels.SetLength(blockChannels);
    PodZero(channels.Elements(), blockChannels);
  } else {
    const nsTArray<const T*>& inputChannels = aInput.ChannelData<T>();
    channels.SetLength(inputChannels.Length());
    PodCopy(channels.Elements(), inputChannels.Elements(), channels.Length());
    if (channels.Length() != blockChannels) {
      // We only need to upmix here because aBlock's channel count has been
      // chosen to be a superset of the channel count of every chunk.
      AudioChannelsUpMix(&channels, blockChannels, static_cast<T*>(nullptr));
    }
  }

  for (uint32_t c = 0; c < blockChannels; ++c) {
    float* outputData = aBlock->ChannelFloatsForWrite(c) + aOffsetInBlock;
    if (channels[c]) {
      ConvertAudioSamplesWithScale(channels[c], outputData, aInput.GetDuration(), aInput.mVolume);
    } else {
      PodZero(outputData, aInput.GetDuration());
    }
  }
}