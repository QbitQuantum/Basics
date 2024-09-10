	void SoundSystem::Update( const float& deltaMilliseconds )
	{
		m_eventSystem->update( );
		m_fmodSystem->update( );

		FMOD::EventCategory* masterCategory = 0;
		m_eventSystem->getCategory( "master", &masterCategory );
		float sfxVolume = static_cast< float >( m_configuration->Find( ConfigSections::Sound, "sfx_volume" ).As< int >( ) ) / 100;
		masterCategory->setVolume( sfxVolume );
	}