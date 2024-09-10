	FMOD::Sound* FMODAudioClip::createStreamingSound() const
	{
		if(getReadMode() != AudioReadMode::Stream || mStreamData == nullptr)
		{
			LOGERR("Invalid audio stream data.");
			return nullptr;
		}

		FMOD_MODE flags = FMOD_CREATESTREAM;

		FMOD_CREATESOUNDEXINFO exInfo;
		memset(&exInfo, 0, sizeof(exInfo));
		exInfo.cbsize = sizeof(exInfo);
		
		// Streaming from memory not supported.
		assert(mStreamData->isFile());

		exInfo.length = mStreamSize;
		exInfo.fileoffset = mStreamOffset;

		SPtr<FileDataStream> fileStream = std::static_pointer_cast<FileDataStream>(mStreamData);
		String pathStr = fileStream->getPath().toString();

		if (is3D())
			flags |= FMOD_3D;
		else
			flags |= FMOD_2D;

		FMOD::Sound* sound = nullptr;
		FMOD::System* fmod = gFMODAudio()._getFMOD();
		if (fmod->createSound(pathStr.c_str(), flags, &exInfo, &sound) != FMOD_OK)
		{
			LOGERR("Failed creating a streaming sound.");
			return nullptr;
		}

		sound->setMode(FMOD_LOOP_OFF);
		return sound;
	}