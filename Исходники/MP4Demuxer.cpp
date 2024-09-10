void
MP4TrackDemuxer::UpdateSamples(nsTArray<nsRefPtr<MediaRawData>>& aSamples)
{
  for (size_t i = 0; i < aSamples.Length(); i++) {
    MediaRawData* sample = aSamples[i];
    if (sample->mCrypto.valid) {
      nsAutoPtr<MediaRawDataWriter> writer(sample->CreateWriter());
      writer->mCrypto.mode = mInfo->mCrypto.mode;
      writer->mCrypto.iv_size = mInfo->mCrypto.iv_size;
      writer->mCrypto.key.AppendElements(mInfo->mCrypto.key);
    }
    if (mInfo->GetAsVideoInfo()) {
      sample->mExtraData = mInfo->GetAsVideoInfo()->mExtraData;
    }
  }
  if (mNextKeyframeTime.isNothing() ||
      aSamples.LastElement()->mTime >= mNextKeyframeTime.value().ToMicroseconds()) {
    SetNextKeyFrameTime();
  }
}