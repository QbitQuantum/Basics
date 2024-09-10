/* -------------------------------------------------------------------------- */
void LensFlare::update()
{
	if (mHidden || !mLightNode) return;

	/// If the Light is out of the Camera field Of View, the lensflare is hidden.
	if (!mCamera->isVisible(getLightPosition()))
	{
		mHaloSet->setVisible(false);
		mBurstSet->setVisible(false);
		return;
	}

	Vector3 lightToCamera = mCamera->getDerivedPosition() - getLightPosition();

	Vector3 CameraVect  = lightToCamera.length() * mCamera->getDerivedDirection();
	CameraVect += mCamera->getDerivedPosition();

	// The LensFlare effect takes place along this vector.
	Vector3 LFvect = (CameraVect - getLightPosition());

//	LFvect += Vector3(-64,-64,0);  // sprite dimension (to be adjusted, but not necessary)

	// The different sprites are placed along this line.
	mHaloSet->getBillboard(0)->setPosition( LFvect);
	mHaloSet->getBillboard(1)->setPosition( LFvect*0.725);
	mHaloSet->getBillboard(2)->setPosition( LFvect*0.250);

	mBurstSet->getBillboard(0)->setPosition( LFvect*0.833);
	mBurstSet->getBillboard(1)->setPosition( LFvect*0.500);
	mBurstSet->getBillboard(2)->setPosition( LFvect*0.320);

	// We redraw the lensflare (in case it was previouly out of the camera field, and hidden)
	this->setVisible(true);
}