void
MediaDecodeTask::FinishDecode()
{
  mDecoderReader->Shutdown();

  uint32_t frameCount = mAudioQueue.FrameCount();
  uint32_t channelCount = mMediaInfo.mAudio.mChannels;
  uint32_t sampleRate = mMediaInfo.mAudio.mRate;

  if (!frameCount || !channelCount || !sampleRate) {
    ReportFailureOnMainThread(WebAudioDecodeJob::InvalidContent);
    return;
  }

  const uint32_t destSampleRate = mDecodeJob.mContext->SampleRate();
  AutoResampler resampler;

  uint32_t resampledFrames = frameCount;
  if (sampleRate != destSampleRate) {
    resampledFrames = static_cast<uint32_t>(
        static_cast<uint64_t>(destSampleRate) *
        static_cast<uint64_t>(frameCount) /
        static_cast<uint64_t>(sampleRate)
      );

    resampler = speex_resampler_init(channelCount,
                                     sampleRate,
                                     destSampleRate,
                                     SPEEX_RESAMPLER_QUALITY_DEFAULT, nullptr);
    speex_resampler_skip_zeros(resampler);
    resampledFrames += speex_resampler_get_output_latency(resampler);
  }

  // Allocate the channel buffers.  Note that if we end up resampling, we may
  // write fewer bytes than mResampledFrames to the output buffer, in which
  // case mWriteIndex will tell us how many valid samples we have.
  bool memoryAllocationSuccess = true;
  if (!mDecodeJob.mChannelBuffers.SetLength(channelCount)) {
    memoryAllocationSuccess = false;
  } else {
    for (uint32_t i = 0; i < channelCount; ++i) {
      mDecodeJob.mChannelBuffers[i] = new (fallible) float[resampledFrames];
      if (!mDecodeJob.mChannelBuffers[i]) {
        memoryAllocationSuccess = false;
        break;
      }
    }
  }
  if (!memoryAllocationSuccess) {
    ReportFailureOnMainThread(WebAudioDecodeJob::UnknownError);
    return;
  }

  nsRefPtr<AudioData> audioData;
  while ((audioData = mAudioQueue.PopFront())) {
    audioData->EnsureAudioBuffer(); // could lead to a copy :(
    AudioDataValue* bufferData = static_cast<AudioDataValue*>
      (audioData->mAudioBuffer->Data());

    if (sampleRate != destSampleRate) {
      const uint32_t maxOutSamples = resampledFrames - mDecodeJob.mWriteIndex;

      for (uint32_t i = 0; i < audioData->mChannels; ++i) {
        uint32_t inSamples = audioData->mFrames;
        uint32_t outSamples = maxOutSamples;

        WebAudioUtils::SpeexResamplerProcess(
            resampler, i, &bufferData[i * audioData->mFrames], &inSamples,
            mDecodeJob.mChannelBuffers[i] + mDecodeJob.mWriteIndex,
            &outSamples);

        if (i == audioData->mChannels - 1) {
          mDecodeJob.mWriteIndex += outSamples;
          MOZ_ASSERT(mDecodeJob.mWriteIndex <= resampledFrames);
          MOZ_ASSERT(inSamples == audioData->mFrames);
        }
      }
    } else {
      for (uint32_t i = 0; i < audioData->mChannels; ++i) {
        ConvertAudioSamples(&bufferData[i * audioData->mFrames],
                            mDecodeJob.mChannelBuffers[i] + mDecodeJob.mWriteIndex,
                            audioData->mFrames);

        if (i == audioData->mChannels - 1) {
          mDecodeJob.mWriteIndex += audioData->mFrames;
        }
      }
    }
  }

  if (sampleRate != destSampleRate) {
    uint32_t inputLatency = speex_resampler_get_input_latency(resampler);
    const uint32_t maxOutSamples = resampledFrames - mDecodeJob.mWriteIndex;
    for (uint32_t i = 0; i < channelCount; ++i) {
      uint32_t inSamples = inputLatency;
      uint32_t outSamples = maxOutSamples;

      WebAudioUtils::SpeexResamplerProcess(
          resampler, i, (AudioDataValue*)nullptr, &inSamples,
          mDecodeJob.mChannelBuffers[i] + mDecodeJob.mWriteIndex,
          &outSamples);

      if (i == channelCount - 1) {
        mDecodeJob.mWriteIndex += outSamples;
        MOZ_ASSERT(mDecodeJob.mWriteIndex <= resampledFrames);
        MOZ_ASSERT(inSamples == inputLatency);
      }
    }
  }

  mPhase = PhaseEnum::AllocateBuffer;
  NS_DispatchToMainThread(this);
}