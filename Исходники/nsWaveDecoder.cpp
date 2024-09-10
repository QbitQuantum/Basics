void
nsWaveStateMachine::CloseAudioStream()
{
  if (mAudioStream) {
    mAudioStream->Shutdown();
    mAudioStream = nsnull;
  }
}