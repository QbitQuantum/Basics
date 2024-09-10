already_AddRefed<MediaRawData>
WAVTrackDemuxer::GetNextChunk(const MediaByteRange& aRange)
{
  if (!aRange.Length()) {
    return nullptr;
  }

  RefPtr<MediaRawData> datachunk = new MediaRawData();
  datachunk->mOffset = aRange.mStart;

  nsAutoPtr<MediaRawDataWriter> chunkWriter(datachunk->CreateWriter());
  if (!chunkWriter->SetSize(aRange.Length())) {
    return nullptr;
  }

  const uint32_t read =
    Read(chunkWriter->Data(), datachunk->mOffset, datachunk->Size());

  if (read != aRange.Length()) {
    return nullptr;
  }

  UpdateState(aRange);
  ++mNumParsedChunks;
  ++mChunkIndex;

  datachunk->mTime = Duration(mChunkIndex - 1);

  if (static_cast<uint32_t>(mChunkIndex) * DATA_CHUNK_SIZE < mDataLength) {
    datachunk->mDuration = Duration(1);
  } else {
    uint32_t mBytesRemaining =
      mDataLength - mChunkIndex * DATA_CHUNK_SIZE;
    datachunk->mDuration = DurationFromBytes(mBytesRemaining);
  }
  datachunk->mTimecode = datachunk->mTime;
  datachunk->mKeyframe = true;

  MOZ_ASSERT(!datachunk->mTime.IsNegative());
  MOZ_ASSERT(!datachunk->mDuration.IsNegative());

  return datachunk.forget();
}