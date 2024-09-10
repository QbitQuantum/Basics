	// When a map is selected in the song wheel
	void OnMapSelected(MapIndex* map)
	{
		if(map == m_currentPreviewAudio)
			return;

		// Set current preview audio
		DifficultyIndex* previewDiff = map->difficulties[0];
		String audioPath = map->path + Path::sep + previewDiff->settings.audioNoFX;

		AudioStream previewAudio = g_audio->CreateStream(audioPath);
		if(previewAudio)
		{
			previewAudio->SetPosition(previewDiff->settings.previewOffset);
			m_previewPlayer.FadeTo(previewAudio);
		}
		else
		{
			Logf("Failed to load preview audio from [%s]", Logger::Warning, audioPath);
			m_previewPlayer.FadeTo(AudioStream());
		}
		m_currentPreviewAudio = map;
	}