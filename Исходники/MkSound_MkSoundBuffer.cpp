bool MkSoundBuffer::SetUp(LPDIRECTSOUND directSound, const MkPathName& filePath)
{
	if (directSound == NULL)
		return false;

	Clear();

	do
	{
		MkStr ext = filePath.GetFileExtension();
		ext.ToLower();

		bool isWave = ext.Equals(0, L"wav");
		bool isOgg = ext.Equals(0, L"ogg");
		
		if ((!isWave) && (!isOgg))
			break;

		// file data
		MkByteArray srcData;
		MK_CHECK(MkFileManager::GetFileData(filePath, srcData), L"음원 파일 로딩 실패 : " + filePath)
			break;

		if (srcData.Empty())
			break;

		if (isWave)
		{
			if (!_CreateBufferFromWaveFile(directSound, srcData))
				break;
		}
		else if (isOgg)
		{
			if (!_CreateBufferFromOggFile(directSound, srcData))
				break;
		}
		else
			break;

		_UpdateInformation();
		return true;
	}
	while (false);

	Clear();
	return false;
}