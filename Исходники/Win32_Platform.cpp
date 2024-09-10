void PlatformCore::PlayMusicFile(const char *fileName)
{
	PlaySoundA(fileName, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
}