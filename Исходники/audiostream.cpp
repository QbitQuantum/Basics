void
AudioStream::GetTimeStretched(AudioBufferWriter& aWriter)
{
  mMonitor.AssertCurrentThreadOwns();

  // We need to call the non-locking version, because we already have the lock.
  if (EnsureTimeStretcherInitializedUnlocked() != NS_OK) {
    return;
  }

  uint32_t toPopFrames =
    ceil(aWriter.Available() * mAudioClock.GetPlaybackRate());

  while (mTimeStretcher->numSamples() < aWriter.Available()) {
    UniquePtr<Chunk> c = mDataSource.PopFrames(toPopFrames);
    if (c->Frames() == 0) {
      break;
    }
    MOZ_ASSERT(c->Frames() <= toPopFrames);
    if (IsValidAudioFormat(c.get())) {
      mTimeStretcher->putSamples(c->Data(), c->Frames());
    } else {
      // Write silence if invalid format.
      AutoTArray<AudioDataValue, 1000> buf;
      buf.SetLength(mOutChannels * c->Frames());
      memset(buf.Elements(), 0, buf.Length() * sizeof(AudioDataValue));
      mTimeStretcher->putSamples(buf.Elements(), c->Frames());
    }
  }

  auto timeStretcher = mTimeStretcher;
  aWriter.Write([timeStretcher] (AudioDataValue* aPtr, uint32_t aFrames) {
    return timeStretcher->receiveSamples(aPtr, aFrames);
  }, aWriter.Available());
}