void
WMFDecoderModule::OnDecodeThreadFinish()
{
  MOZ_ASSERT(!NS_IsMainThread(), "Must be on main thread.");
  CoUninitialize();
}