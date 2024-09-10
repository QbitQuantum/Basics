void CGameData::PlayGunShotSound()
{
	if (mGunShotSound != NULL)
	{
		FMOD::Channel* gunShotChannel;

		mFModSystem->playSound(FMOD_CHANNEL_REUSE, mGunShotSound, false, &gunShotChannel);
		
		gunShotChannel->setMode(FMOD_LOOP_NORMAL);
		gunShotChannel->setLoopCount(0);
	}
}