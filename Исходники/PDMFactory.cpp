already_AddRefed<MediaDataDecoder>
PDMFactory::CreateDecoderWithPDM(PlatformDecoderModule* aPDM,
                                 const CreateDecoderParams& aParams)
{
  MOZ_ASSERT(aPDM);
  RefPtr<MediaDataDecoder> m;
  MediaResult* result = aParams.mError;

  SupportChecker supportChecker;
  const TrackInfo& config = aParams.mConfig;
  supportChecker.AddMediaFormatChecker(config);

  auto checkResult = supportChecker.Check();
  if (checkResult.mReason != SupportChecker::Reason::kSupported) {
    DecoderDoctorDiagnostics* diagnostics = aParams.mDiagnostics;
    if (checkResult.mReason
        == SupportChecker::Reason::kVideoFormatNotSupported) {
      if (diagnostics) {
        diagnostics->SetVideoNotSupported();
      }
      if (result) {
        *result = checkResult.mMediaResult;
      }
    } else if (checkResult.mReason
               == SupportChecker::Reason::kAudioFormatNotSupported) {
      if (diagnostics) {
        diagnostics->SetAudioNotSupported();
      }
      if (result) {
        *result = checkResult.mMediaResult;
      }
    }
    return nullptr;
  }

  if (config.IsAudio()) {
    m = aPDM->CreateAudioDecoder(aParams);
    return m.forget();
  }

  if (!config.IsVideo()) {
    *result = MediaResult(
      NS_ERROR_DOM_MEDIA_FATAL_ERR,
      RESULT_DETAIL("Decoder configuration error, expected audio or video."));
    return nullptr;
  }

  if (MP4Decoder::IsH264(config.mMimeType) && !aParams.mUseNullDecoder) {
    RefPtr<H264Converter> h = new H264Converter(aPDM, aParams);
    const nsresult rv = h->GetLastError();
    if (NS_SUCCEEDED(rv) || rv == NS_ERROR_NOT_INITIALIZED) {
      // The H264Converter either successfully created the wrapped decoder,
      // or there wasn't enough AVCC data to do so. Otherwise, there was some
      // problem, for example WMF DLLs were missing.
      m = h.forget();
    }
  } else {
    m = aPDM->CreateVideoDecoder(aParams);
  }

  return m.forget();
}