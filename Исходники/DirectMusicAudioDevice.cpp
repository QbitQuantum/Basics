//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
AudioPlayer* DirectMusicAudioDevice::CreateAudioPlayer(AudioStream* source, bool enable3d, SoundPlayType type)
{
	RefPtr<DirectMusicAudioPlayer> audioPlayer;

	if (type == SoundPlayType_Midi)
    {
		LN_THROW(DirectMusicManager::GetInstance(), InvalidOperationException);
		audioPlayer.Attach(LN_NEW DirectMusicAudioPlayer(this), false);
		audioPlayer->Initialize(source, enable3d);
    }

	audioPlayer.SafeAddRef();
	return audioPlayer;
}