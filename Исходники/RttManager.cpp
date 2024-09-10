	void RttManager::_initializeRtt(const RttType& Rtt,                        const Ogre::Vector3& PlaneNormal, 
			                        const Ogre::ColourValue& BackgroundColour, const bool& RenderSky, 
									Ogre::RenderTargetListener* RTListener,    const Ogre::String& MaterialScheme, 
									const bool& ShadowsEnabled)
	{
		remove(Rtt);

		mPlanes[Rtt] = new Ogre::MovablePlane(mRttOptions[Rtt].Name + "Plane");
		
		mPlanes[Rtt]->d = 0;
		mPlanes[Rtt]->normal = PlaneNormal;

		Ogre::MeshManager::getSingleton().
			createPlane(mRttOptions[Rtt].Name + "ClipPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                        *mPlanes[Rtt],
                        mHydrax->getMesh()->getSize().Width,mHydrax->getMesh()->getSize().Height, // PG grid.. <-- look into
                        10,10, true, 1,5,5, Ogre::Vector3::UNIT_Z);

		mPlanes[Rtt]->setCastShadows(false);
		mPlanesSceneNode->attachObject(mPlanes[Rtt]);

		Size TSize = mRttOptions[Rtt].Size_;

		if (TSize.Width == 0 || TSize.Height == 0)
		{
			TSize.Width = mHydrax->getViewport()->getActualWidth();
			TSize.Height = mHydrax->getViewport()->getActualHeight();
		}

		mTextures[Rtt] = Ogre::TextureManager::getSingleton()
			.createManual(mRttOptions[Rtt].Name,
                          Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                          Ogre::TEX_TYPE_2D,
                          TSize.Width, 
						  TSize.Height, 
						  0,
						  getPixelFormat(Rtt),
                          Ogre::TU_RENDERTARGET);

        Ogre::RenderTarget* RT_Texture = mTextures[Rtt]->getBuffer()->getRenderTarget();
            
        Ogre::Viewport *RT_Texture_Viewport = RT_Texture->addViewport(mHydrax->getCamera());
        RT_Texture_Viewport->setClearEveryFrame(true);
        RT_Texture_Viewport->setBackgroundColour(BackgroundColour);
        RT_Texture_Viewport->setOverlaysEnabled(false);
		RT_Texture_Viewport->setShadowsEnabled(ShadowsEnabled);
		if (MaterialScheme != "")
		{
            RT_Texture_Viewport->setMaterialScheme(MaterialScheme);
		}
        RT_Texture_Viewport->setSkiesEnabled(RenderSky);

        RT_Texture->addListener(RTListener);
	}