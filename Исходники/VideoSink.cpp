void
VideoSink::RenderVideoFrames(int32_t aMaxFrames,
                             int64_t aClockTime,
                             const TimeStamp& aClockTimeStamp)
{
  AssertOwnerThread();

  AutoTArray<RefPtr<MediaData>,16> frames;
  VideoQueue().GetFirstElements(aMaxFrames, &frames);
  if (frames.IsEmpty() || !mContainer) {
    return;
  }

  AutoTArray<ImageContainer::NonOwningImage,16> images;
  TimeStamp lastFrameTime;
  MediaSink::PlaybackParams params = mAudioSink->GetPlaybackParams();
  for (uint32_t i = 0; i < frames.Length(); ++i) {
    VideoData* frame = frames[i]->As<VideoData>();

    frame->mSentToCompositor = true;

    if (!frame->mImage || !frame->mImage->IsValid() ||
        !frame->mImage->GetSize().width || !frame->mImage->GetSize().height) {
      continue;
    }

    int64_t frameTime = frame->mTime;
    if (frameTime < 0) {
      // Frame times before the start time are invalid; drop such frames
      continue;
    }

    TimeStamp t;
    if (aMaxFrames > 1) {
      MOZ_ASSERT(!aClockTimeStamp.IsNull());
      int64_t delta = frame->mTime - aClockTime;
      t = aClockTimeStamp +
          TimeDuration::FromMicroseconds(delta / params.mPlaybackRate);
      if (!lastFrameTime.IsNull() && t <= lastFrameTime) {
        // Timestamps out of order; drop the new frame. In theory we should
        // probably replace the previous frame with the new frame if the
        // timestamps are equal, but this is a corrupt video file already so
        // never mind.
        continue;
      }
      lastFrameTime = t;
    }

    ImageContainer::NonOwningImage* img = images.AppendElement();
    img->mTimeStamp = t;
    img->mImage = frame->mImage;
    img->mFrameID = frame->mFrameID;
    img->mProducerID = mProducerID;

    VSINK_LOG_V("playing video frame %lld (id=%x) (vq-queued=%i)",
                frame->mTime, frame->mFrameID, VideoQueue().GetSize());
  }
  mContainer->SetCurrentFrames(frames[0]->As<VideoData>()->mDisplay, images);
}