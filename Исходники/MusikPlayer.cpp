void CMusikPlayer::FinalizePause()
{
	m_SndEngine.SetPlayState( MUSIKEngine::Paused );
	m_Paused = true;
    MusikPlayerEvent ev_pause(this,wxEVT_MUSIKPLAYER_PLAY_PAUSE);
    ProcessEvent(ev_pause);

}