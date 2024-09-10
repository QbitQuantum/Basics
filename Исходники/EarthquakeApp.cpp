void EarthquakeApp::setup()
{
	gl::Texture earthDiffuse	= gl::Texture( loadImage( loadResource( RES_EARTHDIFFUSE ) ) );
	gl::Texture earthNormal		= gl::Texture( loadImage( loadResource( RES_EARTHNORMAL ) ) );
	gl::Texture earthMask		= gl::Texture( loadImage( loadResource( RES_EARTHMASK ) ) );
	earthDiffuse.setWrap( GL_REPEAT, GL_REPEAT );
	earthNormal.setWrap( GL_REPEAT, GL_REPEAT );
	earthMask.setWrap( GL_REPEAT, GL_REPEAT );

	mStars						= gl::Texture( loadImage( loadResource( RES_STARS_PNG ) ) );

	
	mEarthShader = gl::GlslProg( loadResource( RES_PASSTHRU_VERT ), loadResource( RES_EARTH_FRAG ) );
	mQuakeShader = gl::GlslProg( loadResource( RES_QUAKE_VERT ), loadResource( RES_QUAKE_FRAG ) );

	
	mCounter		= 0.0f;
	mCurrentFrame	= 0;
	mSaveFrames		= false;
	mShowEarth		= true;
	mShowText		= true;
	mShowQuakes		= true;
	mLightDir		= vec3( 0.025f, 0.25f, 1.0f );
	mLightDir.normalize();
	mPov			= POV( this, ci::vec3( 0.0f, 0.0f, 1000.0f ), ci::vec3( 0.0f, 0.0f, 0.0f ) );
	mEarth			= Earth( earthDiffuse, earthNormal, earthMask );
	
	parseEarthquakes( "http://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/2.5_week.geojson" );
	
	mEarth.setQuakeLocTip();
}