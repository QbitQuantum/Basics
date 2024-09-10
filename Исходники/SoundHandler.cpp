LC3Sound::LC3Sound()
{
	memset(table, 0, sizeof(table));
	timeLeft = 0;
	tableIndex = 0;
	hwnd = GetForegroundWindow();
	DirectSoundCreate(NULL, &lpDirectSound, NULL);
	AppCreateWritePrimaryBuffer( lpDirectSound, &lpDirectSoundBuffer, hwnd);
	LoadSamp(lpDirectSound, &lpSwSamp, NULL, BUFSIZE, DSBCAPS_LOCSOFTWARE);
	lpDirectSound->SetCooperativeLevel(hwnd, DSSCL_NORMAL);
	//lpDirectSound->Initialize(&soundGUID);
	lpSwSamp->Play(0, 0, DSBPLAY_LOOPING);
	soundData = (char*)malloc(BUFSIZE);
	gwid = timeSetEvent( 40, 40, TimeProcC, (unsigned long) this, TIME_PERIODIC);
}