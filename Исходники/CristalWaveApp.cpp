void CristalWaveApp::setup()
{
	float sizeW = getWindowWidth() * 0.5f;
	float sizeH = getWindowHeight() * 0.5f;
	float	x = 0.0f,
			z = 0.0f,
			y = 0.0f;

	/////////////////////////////////////////////////
	int numRows = PARAM_WAVE_NB_ROWS;
	int gap = PARAM_WAVE_GAP + getWindowWidth() / 2000;
	int numLines = getWindowWidth() / gap + 1;
	/////////////////////////////////////////////////

	mOpacity = 0.0f;
	mOffsetCameratH = 60; // Global amplitude

	// Init BackgroundLayer
	mBackground.setup(getWindowWidth(), getWindowHeight(), mOffsetCameratH);

	// Init Wave Model
	mWave.setup(getWindowWidth(), getWindowHeight(), numRows, numLines, -mOffsetCameratH);

	// set a random offset
	Rand rnd;
	rnd.seed((unsigned long)GetTickCount());
	mOffsetTime = rnd.nextFloat(0.0f, 100.0f);

	// Set the Shader program
	mFresnelShader.load();
	mpWaveShader = &mFresnelShader;
	mWave.setShader(mpWaveShader);

	// --------------------------------------------------------
	// Set Particule manager
	int nbParticule = PARAM_NB_PARTICULES;
	mEmitter.radius = PARAM_EMITTER_RADIUS;

	mParticuleInTheWindManager.attrPosition = Vec3f::zero();
	mParticuleInTheWindManager.attrFactor = PARAM_FORCE_FACTOR;

	ParticuleManager::PARTICULE_LIFE particule_life;
	particule_life.minTTL = 0.5f;
	particule_life.maxTTL = 3.5f;
	particule_life.minTTH = 1.0f;
	particule_life.minTTH = 4.0f;
	mParticuleInTheWindManager.init(nbParticule, particule_life, getWindowWidth());
}