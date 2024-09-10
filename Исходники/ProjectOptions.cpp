void ProjectOptions::InitDevInfo()
{
	long id = 0;
	HMODULE h = LoadLibrary("dsound.dll");
	if (h)
	{
		tDirectSoundEnumerate pDirectSoundEnumerate = (tDirectSoundEnumerate)GetProcAddress(h, "DirectSoundEnumerateA");
		if (pDirectSoundEnumerate)
			pDirectSoundEnumerate(EnumWaveDevice, &id);
	}

	UINT ndev = midiInGetNumDevs();
	for (UINT n = 0; n < ndev; n++)
	{
		MIDIINCAPS caps;
		memset(&caps, 0, sizeof(caps));
		midiInGetDevCaps(n, &caps, sizeof(caps));
		SoundDevInfo *inf = midiList.AddItem();
		inf->name = caps.szPname;
		inf->info = NULL;
		inf->id = (long)n;
		inf->sub = 0;
		inf->type = 1;
	}
}