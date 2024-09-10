void C_SoundscapeSystem::Shutdown()
{
	for ( int i = m_loopingSounds.Count() - 1; i >= 0; --i )
	{
		loopingsound_t &sound = m_loopingSounds[i];

		// sound is done, remove from list.
		StopLoopingSound( sound );
	}
	
	// These are only necessary so we can use shutdown/init calls
	// to flush soundscape data
	m_loopingSounds.RemoveAll();
	m_randomSounds.RemoveAll();
	m_soundscapes.RemoveAll();
	m_params.ent.Set( NULL );
	m_params.soundscapeIndex = -1;

	while ( m_SoundscapeScripts.Count() > 0 )
	{
		KeyValues *kv = m_SoundscapeScripts[ 0 ];
		m_SoundscapeScripts.Remove( 0 );
		kv->deleteThis();
	}
}