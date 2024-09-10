void AudioObjApp::update()
{
	if ( mFeature )
	{
		mFeature->setDamping( mFeatureDamping );
		mFeature->setGain( mFeatureGain );
		mFeature->setOffset( mFeatureOffset );
	}

    mXtract->update();

	if ( mFeature )
	{
		// update Surface
		int x, y;
		for( int k=0; k < mFeature->getSize(); k++ )
		{
			x = k % mFeatureSurf.getWidth();
			y = k / mFeatureSurf.getWidth();
			mFeatureSurf.setPixel( Vec2i(x, y), Color::gray( mFeature->getDataValue(k) ) );
		}
		mFeatureTex = gl::Texture( mFeatureSurf );
	}
}