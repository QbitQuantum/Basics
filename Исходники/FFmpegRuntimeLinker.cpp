/* static */ bool
FFmpegRuntimeLinker::Link()
{
  if (sLinkStatus) {
    return sLinkStatus == LinkStatus_SUCCEEDED;
  }

  MOZ_ASSERT(NS_IsMainThread());

  for (size_t i = 0; i < ArrayLength(sLibs); i++) {
    const AvCodecLib* lib = &sLibs[i];
    sLinkedLib = dlopen(lib->Name, RTLD_NOW | RTLD_LOCAL);
    if (sLinkedLib) {
      if (Bind(lib->Name, lib->Version)) {
        sLib = lib;
        sLinkStatus = LinkStatus_SUCCEEDED;
        return true;
      }
      // Shouldn't happen but if it does then we try the next lib..
      Unlink();
    }
  }

  FFMPEG_LOG("H264/AAC codecs unsupported without [");
  for (size_t i = 0; i < ArrayLength(sLibs); i++) {
    FFMPEG_LOG("%s %s", i ? "," : "", sLibs[i].Name);
  }
  FFMPEG_LOG(" ]\n");

  Unlink();

  sLinkStatus = LinkStatus_FAILED;
  return false;
}