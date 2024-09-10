	void Sound::create (Movable *parent)
	{
		Ogre::SceneManager *mSceneMgr = RadXML::getSingletonPtr ()->getSceneManager ();

		if (load == true)
		{
			sSound = new RadXmlCommon::s13Sound ();
			sSound->strPath = file;
			sSound->bStreaming = streaming;
			sSound->dGain = gain;
			sSound->LoadPath ();

			if (sSound->IsLoaded () == false)
				RadXmlCommon::s13LogMessage ("Unable to load audio file: " + file);

			if (bPlay == true)
				sSound->Play ();
		}

		/// @note Create the SceneNode here and keep it updated.
		updateSettings ();
		setParent (parent);
	}