bool Player::Create()
{
	if (FAILED(XAudio2Create(&AudioDriver, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return false;

	if (FAILED(AudioDriver->CreateMasteringVoice(&AudioMVoice)))
		return false;

	return true;
}