/*
 * Create an CSDLAudioSync for a session.  Don't alloc any buffers until
 * config is called by codec
 */
CSDLAudioSync::CSDLAudioSync (CPlayerSession *psptr, int volume) :
  CBufferAudioSync(psptr, volume)
{
  Our_SDL_AudioInit(getenv("SDL_AUDIODRIVER"));
  m_volume = (volume * SDL_MIX_MAXVOLUME)/100;
}