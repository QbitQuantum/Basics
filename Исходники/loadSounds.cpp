void			playBackground(void)
{
	FMOD::System *		Syst = NULL;
	FMOD::Channel *		Chan = NULL;
	FMOD::Sound *		s;

	if (Syst == NULL)
	{
		if (FMOD::System_Create(&Syst) != FMOD_OK)
			fmod_exit();
		if (Syst->init(32, FMOD_INIT_NORMAL, 0) != FMOD_OK)
			fmod_exit();
	}
	if (Syst->createSound("mp3/background.mp3", FMOD_LOOP_NORMAL, 0, &s) != FMOD_OK)
		fmod_exit();
	if (Syst->playSound(s, NULL, false, &Chan) != FMOD_OK)
		fmod_exit();
	Syst->update();
}