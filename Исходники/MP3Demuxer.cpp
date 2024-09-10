already_AddRefed<MediaRawData>
MP3TrackDemuxer::GetNextFrame(const MediaByteRange& aRange) {
  MP3LOG("GetNext() Begin({mStart=%" PRId64 " Length()=%" PRId64 "})",
         aRange.mStart, aRange.Length());
  if (!aRange.Length()) {
    return nullptr;
  }

  RefPtr<MediaRawData> frame = new MediaRawData();
  frame->mOffset = aRange.mStart;

  nsAutoPtr<MediaRawDataWriter> frameWriter(frame->CreateWriter());
  if (!frameWriter->SetSize(aRange.Length())) {
    MP3LOG("GetNext() Exit failed to allocated media buffer");
    return nullptr;
  }

  const uint32_t read = Read(frameWriter->Data(), frame->mOffset, frame->Size());

  if (read != aRange.Length()) {
    MP3LOG("GetNext() Exit read=%u frame->Size()=%u", read, frame->Size());
    return nullptr;
  }

  UpdateState(aRange);

  frame->mTime = Duration(mFrameIndex - 1).ToMicroseconds();
  frame->mDuration = Duration(1).ToMicroseconds();
  frame->mTimecode = frame->mTime;
  frame->mKeyframe = true;

  MOZ_ASSERT(frame->mTime >= 0);
  MOZ_ASSERT(frame->mDuration > 0);

  if (mNumParsedFrames == 1) {
    // First frame parsed, let's read VBR info if available.
    // TODO: read info that helps with seeking (bug 1163667).
    ByteReader reader(frame->Data(), frame->Size());
    mParser.ParseVBRHeader(&reader);
    reader.DiscardRemaining();
    mFirstFrameOffset = frame->mOffset;
  }

  MP3LOGV("GetNext() End mOffset=%" PRIu64 " mNumParsedFrames=%" PRIu64
          " mFrameIndex=%" PRId64 " mTotalFrameLen=%" PRIu64
          " mSamplesPerFrame=%d mSamplesPerSecond=%d mChannels=%d",
          mOffset, mNumParsedFrames, mFrameIndex, mTotalFrameLen,
          mSamplesPerFrame, mSamplesPerSecond, mChannels);

  return frame.forget();
}