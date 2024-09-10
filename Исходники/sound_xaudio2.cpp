//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void InitSound()
{
	HRESULT hr;
	
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	hr = XAudio2Create(&g_xaudio2, 0);
	hr = g_xaudio2->CreateMasteringVoice(&g_masteringVoice, 2, 44100);

	g_sound = EffekseerSound::Sound::Create(g_xaudio2, 16, 16);
	
	g_manager->SetSoundPlayer( g_sound->CreateSoundPlayer() );
	g_manager->SetSoundLoader( g_sound->CreateSoundLoader() );
}